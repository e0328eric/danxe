use thiserror::Error;

#[derive(Debug, Error)]
pub enum DanxeErr {
    #[error("{0}")]
    FromFailed(#[from] FromBytesErr),
}

#[derive(Debug, Error)]
pub enum FromBytesErr {
    #[error("cannot parse bytes into a number")]
    FailedToMakeNumber,
    #[error("cannot parse bytes into a character")]
    FailedToMakeChar,
    #[error("cannot parse bytes into a string")]
    FailedToMakeString,
    #[error("cannot parse bytes into a vector")]
    FailedToMakeVector,
}

#[macro_export]
macro_rules! danxe_err {
    (FromBytesErr::$from_bytes_err: ident) => {
        DanxeErr::FromFailed(FromBytesErr::$from_bytes_err)
    };
}

pub type Result<T> = error_stack::Result<T, DanxeErr>;
