// Copyright (c) 2023 Sungbae Jeong
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

use std::ops::{Add, Div, Mul, Not, Sub};

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
