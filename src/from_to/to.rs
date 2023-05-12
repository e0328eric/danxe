use std::fs;
use std::io::{self, BufWriter, Write};
use std::mem::size_of;
use std::path::Path;

use crate::from_to::{BYTES_END, BYTES_SEPARATOR, BYTES_START, STRING_END, STRING_START};

pub trait ToBytes {
    fn to_bytes(&self) -> Vec<u8>;

    fn write_into(&self, writer: impl Write) -> io::Result<()> {
        let mut buf_writer = BufWriter::new(writer);
        buf_writer.write_all(&self.to_bytes())
    }

    fn write_into_file(&self, filename: impl AsRef<Path>) -> io::Result<()> {
        self.write_into(fs::File::create(filename)?)
    }
}

// Implementations for primitive types

impl ToBytes for bool {
    fn to_bytes(&self) -> Vec<u8> {
        vec![*self as u8]
    }
}

impl ToBytes for i64 {
    fn to_bytes(&self) -> Vec<u8> {
        Vec::from(self.to_le_bytes())
    }
}

impl ToBytes for u64 {
    fn to_bytes(&self) -> Vec<u8> {
        Vec::from(self.to_le_bytes())
    }
}

impl ToBytes for f64 {
    fn to_bytes(&self) -> Vec<u8> {
        Vec::from(self.to_le_bytes())
    }
}

impl ToBytes for char {
    fn to_bytes(&self) -> Vec<u8> {
        Vec::from((*self as u32).to_le_bytes())
    }
}

impl ToBytes for String {
    fn to_bytes(&self) -> Vec<u8> {
        let mut output = Vec::with_capacity(self.len() + 2);
        output.push(STRING_START);
        output.append(&mut Vec::from(self.as_bytes()));
        output.push(STRING_END);

        output
    }
}

impl<T> ToBytes for Vec<T>
where
    T: ToBytes,
{
    fn to_bytes(&self) -> Vec<u8> {
        let mut output = Vec::with_capacity((size_of::<T>() + 1) * self.len() + 2);

        output.push(BYTES_START);
        for byte in
            itertools::intersperse(self.iter().map(|val| val.to_bytes()), vec![BYTES_SEPARATOR])
                .flatten()
        {
            output.push(byte);
        }
        output.push(BYTES_END);

        output
    }
}
