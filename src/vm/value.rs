use std::cmp::Ordering;
use std::ops::{Add, Div, Mul, Rem, Sub};

use serde::{Deserialize, Serialize};

#[repr(u8)]
#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
pub enum Value {
    Null = 0,
    Bool(bool),
    Int(i64),
    Uint(u64),
    Float(f64),
    Str(String),
    Array(Vec<Value>),
}

impl PartialOrd for Value {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        match (self, other) {
            (Self::Null, Self::Null) => Some(Ordering::Equal),
            (Self::Bool(b1), Self::Bool(b2)) => b1.partial_cmp(b2),
            (Self::Int(n1), Self::Int(n2)) => n1.partial_cmp(n2),
            (Self::Float(n1), Self::Float(n2)) => n1.partial_cmp(n2),
            _ => None,
        }
    }
}

impl Add for Value {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 + n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 + n2),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 + n2),
            (Self::Str(str1), Self::Str(str2)) => Self::Str(str1 + &str2),
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

    fn sub(self, rhs: Self) -> Self::Output {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 - n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 - n2),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 - n2),
            _ => Self::Null,
        }
    }
}

impl Mul for Value {
    type Output = Self;

    fn mul(self, rhs: Self) -> Self::Output {
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

    fn div(self, rhs: Self) -> Self::Output {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 / n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 / n2),
            (Self::Float(n1), Self::Float(n2)) => Self::Float(n1 / n2),
            _ => Self::Null,
        }
    }
}

impl Rem for Value {
    type Output = Self;

    fn rem(self, rhs: Self) -> Self::Output {
        match (self, rhs) {
            (Self::Int(n1), Self::Int(n2)) => Self::Int(n1 % n2),
            (Self::Uint(n1), Self::Uint(n2)) => Self::Uint(n1 % n2),
            _ => Self::Null,
        }
    }
}
