use std::ops::{Add, Div, Mul, Not, Sub};

use crate::from_to::to::ToBytes;

#[repr(u8)]
#[derive(Debug, Clone, PartialEq)]
pub enum Value {
    Null = 0,
    Bool(bool),
    Int(i64),
    Uint(u64),
    Float(f64),
    Char(char),
    String(String),
    Array(Vec<Value>),
}

// Operator Overloadings

impl Add for Value {
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 + n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 + n2),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 + n2),
            (Self::String(mut s1), Self::String(s2)) => {
                s1.push_str(&s2);
                Self::String(s1)
            }
            (Self::Array(mut arr1), Self::Array(mut arr2)) => {
                arr1.append(&mut arr2);
                Self::Array(arr1)
            }
            _ => Self::Null,
        }
    }
}

impl Sub for Value {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 - n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1.saturating_sub(n2)),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 - n2),
            _ => Self::Null,
        }
    }
}

impl Mul for Value {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 * n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 * n2),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 * n2),
            _ => Self::Null,
        }
    }
}

impl Div for Value {
    type Output = Self;
    fn div(self, rhs: Self) -> Self {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 / n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 / n2),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 / n2),
            _ => Self::Null,
        }
    }
}

impl Not for Value {
    type Output = Self;
    fn not(self) -> Self {
        match self {
            Self::Null => Self::Bool(true),
            Self::Bool(b) => Self::Bool(!b),
            _ => Self::Null,
        }
    }
}

// FromBytes and ToBytes implementation

impl ToBytes for Value {
    fn to_bytes(&self) -> Vec<u8> {
        match self {
            Self::Null => vec![0],
            Self::Bool(b) => vec![1, (*b as u8)],
            Self::Int(n) => {
                let mut output = vec![2];
                output.append(&mut n.to_bytes());
                output
            }
            Self::Uint(n) => {
                let mut output = vec![3];
                output.append(&mut n.to_bytes());
                output
            }
            Self::Float(n) => {
                let mut output = vec![4];
                output.append(&mut n.to_bytes());
                output
            }
            Self::Char(chr) => {
                let mut output = vec![5];
                output.append(&mut chr.to_bytes());
                output
            }
            Self::String(s) => {
                let mut output = vec![6];
                output.append(&mut s.to_bytes());
                output
            }
            Self::Array(arr) => {
                let mut output = vec![7];
                output.append(&mut arr.to_bytes());
                output
            }
        }
    }
}
