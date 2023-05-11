mod command;

use danxe::from_to::to::ToBytes;
use danxe::vm::value::Value;

fn main() {
    let values = Value::Array(vec![
        Value::Null,
        Value::Array(vec![
            Value::String("麻婆豆腐大块的，请多放点花椒。".to_string()),
            Value::Float(std::f64::consts::PI),
            Value::Int(123),
            Value::Char('강'),
        ]),
        Value::Bool(true),
    ]);

    println!("{:?}", values.to_bytes());
}
