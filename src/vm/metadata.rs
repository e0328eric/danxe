use serde::{Deserialize, Serialize};

const MAGIC: u64 = 0x64616E7865;

#[derive(Debug, Clone, Copy, Serialize, Deserialize)]
struct Metadata {
    magic: u64,
    version: u32,
    program_start: u64,
    memory_start: u64,
}
