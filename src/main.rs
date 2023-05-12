mod command;

use danxe::error;
use danxe::from_to::from::FromBytes;
use danxe::from_to::to::ToBytes;
use danxe::vm::value::Value;

fn main() -> error::Result<()> {
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

    let strings = vec![
        String::from("Hello, World!"),
        String::from("麻婆豆腐大块的，请多放点花椒。"),
        String::from("잘 만들어져야 한다."),
        String::from("ども、サメです。"),
    ];

    let bytes = strings.to_bytes();
    println!("{:x?}", bytes);

    let parsed = Vec::<String>::from_bytes(&bytes)?.0;
    println!("{parsed:?}");

    Ok(())
}
