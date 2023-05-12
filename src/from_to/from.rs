use std::mem::size_of;

use error_stack::{bail, report, IntoReport, ResultExt};

use crate::error::{self, DanxeErr, FromBytesErr};
use crate::from_to::{BYTES_END, BYTES_SEPARATOR, BYTES_START, STRING_END, STRING_START};

pub trait FromBytes: Sized {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])>;

    fn from_bytes_mut(bytes: &mut &[u8]) -> error::Result<Self> {
        let (output, rest) = Self::from_bytes(*bytes)?;
        *bytes = rest;
        Ok(output)
    }
}

// Implementations for primitive types

impl FromBytes for bool {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        let (bool_bytes, rest) = bytes.split_at(1);
        Ok((matches!(bool_bytes[0], 1), rest))
    }
}

impl FromBytes for i64 {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        let (int_bytes, rest) = bytes.split_at(size_of::<Self>());
        Ok((
            Self::from_le_bytes(
                int_bytes
                    .try_into()
                    .into_report()
                    .change_context(danxe_err!(FromBytesErr::FailedToMakeNumber))?,
            ),
            rest,
        ))
    }
}
impl FromBytes for u64 {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        let (int_bytes, rest) = bytes.split_at(size_of::<Self>());
        Ok((
            Self::from_le_bytes(
                int_bytes
                    .try_into()
                    .into_report()
                    .change_context(danxe_err!(FromBytesErr::FailedToMakeNumber))?,
            ),
            rest,
        ))
    }
}

impl FromBytes for f64 {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        let (float_bytes, rest) = bytes.split_at(size_of::<Self>());
        Ok((
            Self::from_le_bytes(
                float_bytes
                    .try_into()
                    .into_report()
                    .change_context(danxe_err!(FromBytesErr::FailedToMakeNumber))?,
            ),
            rest,
        ))
    }
}

impl FromBytes for char {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        let (char_bytes, rest) = bytes.split_at(size_of::<u32>());
        let char_as_u32 = u32::from_le_bytes(
            char_bytes
                .try_into()
                .into_report()
                .change_context(danxe_err!(FromBytesErr::FailedToMakeChar))
                .attach_printable_lazy(|| "failed to convert `char_bytes` array into a slice")?,
        );
        Ok((
            char::from_u32(char_as_u32)
                .ok_or(report!(danxe_err!(FromBytesErr::FailedToMakeChar)))
                .attach_printable_lazy(|| "given bytes has an invalid UTF-8 format")?,
            rest,
        ))
    }
}

impl FromBytes for String {
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        if bytes[0] != STRING_START {
            let report = report!(danxe_err!(FromBytesErr::FailedToMakeString))
                .attach_printable("cannot found `STRING_START` special byte in the given bytes");
            return Err(report);
        }
        let Some(string_end_idx) = bytes.iter().position(|b| *b == STRING_END) else {
            let report = report!(danxe_err!(FromBytesErr::FailedToMakeString))
                .attach_printable("cannot found `STRING_END` special byte in the given bytes");
            return Err(report);
        };

        let (string_bytes, rest) = (&bytes[1..string_end_idx], &bytes[string_end_idx + 1..]);
        Ok((
            String::from_utf8(string_bytes.to_vec())
                .into_report()
                .change_context(danxe_err!(FromBytesErr::FailedToMakeString))
                .attach_printable_lazy(|| "inner bytes has an invalid UTF-8 string format")?,
            rest,
        ))
    }
}

impl<T> FromBytes for Vec<T>
where
    T: FromBytes,
{
    fn from_bytes(bytes: &[u8]) -> error::Result<(Self, &[u8])> {
        if bytes[0] != BYTES_START {
            let report = report!(danxe_err!(FromBytesErr::FailedToMakeVector))
                .attach_printable("cannot found `BYTES_START` special byte in the given bytes");
            return Err(report);
        }
        let Some(array_end_idx) = bytes.iter().position(|b| *b == BYTES_END) else {
            let report = report!(danxe_err!(FromBytesErr::FailedToMakeVector))
                .attach_printable("cannot found `BYTES_END` special byte in the given bytes");
            return Err(report);
        };

        let mut output = Vec::with_capacity(10);
        for subbytes in bytes[1..array_end_idx].split(|b| *b == BYTES_SEPARATOR) {
            let (val, rest) = T::from_bytes(subbytes)?;
            if !rest.is_empty() {
                bail!(danxe_err!(FromBytesErr::FailedToMakeVector));
            }
            output.push(val);
        }

        Ok((output, &bytes[array_end_idx + 1..]))
    }
}
