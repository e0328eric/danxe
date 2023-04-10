use serde::{Deserialize, Serialize};

macro_rules! impl_opcode {
    ($(($opcode: ident, $opcode_str: literal),)+) => {
        #[repr(u8)]
        #[derive(Debug, Clone, Copy, Serialize, Deserialize)]
        pub enum Opcode {
            $($opcode,)+
            Invalid = 0xFF,
        }

        impl From<&str> for Opcode {
            fn from(s: &str) -> Self {
                match s {
                    $($opcode_str => Self::$opcode,)+
                    _ => Self::Invalid,
                }
            }
        }

        impl From<Opcode> for &str {
            fn from(opcode: Opcode) -> &'static str {
                match opcode {
                    $(Opcode::$opcode => $opcode_str,)+
                    Opcode::Invalid => "INVALID",
                }
            }
        }
    };
}

impl_opcode![
    (Nop, "nop"),
    (Push, "push"),
    (Pop, "pop"),
    (Add, "add"),
    (Sub, "sub"),
    (Mul, "mul"),
    (Div, "div"),
    (Rem, "rem"),
    (Inc, "inc"),
    (Dec, "dec"),
    (Halt, "halt"),
];
