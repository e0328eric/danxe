pub mod from;
pub mod to;

pub(in crate::from_to) const BYTES_START: u8 = 0xfa;
pub(in crate::from_to) const BYTES_SEPARATOR: u8 = 0xfb;
pub(in crate::from_to) const BYTES_END: u8 = 0xfc;

pub(in crate::from_to) const STRING_START: u8 = 0xfd;
pub(in crate::from_to) const STRING_END: u8 = 0xfe;

// A marker trait which indicates whether a type has
// both FromBytes and ToBytes implementations
pub trait FromToBytes: from::FromBytes + to::ToBytes {}

// Implementations for primitive types

impl FromToBytes for bool {}
impl FromToBytes for i64 {}
impl FromToBytes for u64 {}
impl FromToBytes for f64 {}
impl FromToBytes for char {}
impl FromToBytes for String {}
impl<T> FromToBytes for Vec<T> where T: FromToBytes {}

#[cfg(test)]
mod tests {
    use rand::distributions::{DistString, Standard};
    use rand::prelude::{thread_rng, Rng};

    use super::super::error;
    use super::from::FromBytes;
    use super::to::ToBytes;

    #[test]
    fn test_from_to_for_bool() -> error::Result<()> {
        let mut rng = thread_rng();
        let bools = (&mut rng)
            .sample_iter(Standard)
            .take(101)
            .collect::<Vec<bool>>();

        for b in bools {
            let bytes = b.to_bytes();
            let (got, rest) = bool::from_bytes(&bytes)?;

            assert!(rest.is_empty());
            assert_eq!(b, got);
        }

        Ok(())
    }

    #[test]
    fn test_from_to_for_int() -> error::Result<()> {
        let mut rng = thread_rng();
        let ints = (&mut rng)
            .sample_iter(Standard)
            .take(101)
            .collect::<Vec<i64>>();

        for i in ints {
            let bytes = i.to_bytes();
            let (got, rest) = i64::from_bytes(&bytes)?;

            assert!(rest.is_empty());
            assert_eq!(i, got);
        }

        Ok(())
    }

    #[test]
    fn test_from_to_for_uint() -> error::Result<()> {
        let mut rng = thread_rng();
        let uints = (&mut rng)
            .sample_iter(Standard)
            .take(101)
            .collect::<Vec<u64>>();

        for n in uints {
            let bytes = n.to_bytes();
            let (got, rest) = u64::from_bytes(&bytes)?;

            assert!(rest.is_empty());
            assert_eq!(n, got);
        }

        Ok(())
    }

    #[test]
    fn test_from_to_for_float() -> error::Result<()> {
        let mut rng = thread_rng();
        let floats = (&mut rng)
            .sample_iter(Standard)
            .take(101)
            .collect::<Vec<f64>>();

        for x in floats {
            let bytes = x.to_bytes();
            let (got, rest) = f64::from_bytes(&bytes)?;

            assert!(rest.is_empty());
            assert_eq!(x, got);
        }

        Ok(())
    }

    #[test]
    fn test_from_to_for_char() -> error::Result<()> {
        let mut rng = thread_rng();
        let chars = (&mut rng)
            .sample_iter(Standard)
            .take(101)
            .collect::<Vec<char>>();

        for chr in chars {
            let bytes = chr.to_bytes();
            let (got, rest) = char::from_bytes(&bytes)?;

            assert!(rest.is_empty());
            assert_eq!(chr, got);
        }

        Ok(())
    }

    #[test]
    fn test_from_to_for_string() -> error::Result<()> {
        let mut rng = thread_rng();
        let mut strings = Vec::<String>::with_capacity(101);

        let mut len_rng = thread_rng();
        for _ in 0..101 {
            strings.push(Standard.sample_string(&mut rng, len_rng.gen_range(1..101)));
        }

        for s in strings {
            let bytes = s.to_bytes();
            let (got, rest) = String::from_bytes(&bytes)?;

            assert!(rest.is_empty());
            assert_eq!(s, got);
        }

        Ok(())
    }

    #[test]
    fn test_from_to_for_vector() -> error::Result<()> {
        let mut rng = thread_rng();
        let mut array = Vec::<String>::with_capacity(101);

        let mut len_rng = thread_rng();
        for _ in 0..101 {
            array.push(Standard.sample_string(&mut rng, len_rng.gen_range(1..101)));
        }

        let bytes = array.to_bytes();
        let (got, rest) = Vec::<String>::from_bytes(&bytes)?;

        assert!(rest.is_empty());
        assert_eq!(array, got);

        Ok(())
    }
}
