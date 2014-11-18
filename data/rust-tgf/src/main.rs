extern crate getopts;
use getopts::{optopt,optflag,getopts,OptGroup};
use std::os;
use std::io::fs::File;
use std::rand;

fn gen_matrix(size: f64, prod_rate: int, nodes: uint, sinks: uint, mut out: Box<Writer>) {
    //Define Nodes (id, x-pos, y-pos, opt. production rate)
    let mut i_range = std::iter::range(0u, nodes);
    match out.write((nodes.to_string() + "\n").as_bytes()) {
        Ok(()) => (),
        Err(e) => panic!(e.desc)
    };
    for i in i_range {
        let x_val = size*rand::random::<f64>();
        let y_val = size*rand::random::<f64>();
        let mut output : String = i.to_string() + " " + x_val.to_string() + " " + y_val.to_string();
        if i<= sinks {
            output = output + " ";
        }
        //If Source
        if i==0 {
            output = output + prod_rate.to_string();
        //If Sink
        } else if i <= sinks {
            output = output + "-" + (prod_rate as int).to_string();
        }
        output = output + "\n";
        match out.write(output.as_bytes()) {
            Ok(()) => (),
            Err(e) => panic!(e.desc)
        };
    }
    return;
}

fn print_usage(program: &str, _opts: &[OptGroup]) {
    println!("Usage: {} [options]", program);
    println!("-o\t\tOutput filename");
    println!("-p\t\tProduction rate of central source");
    println!("-n\t\tNumber of Nodes");
    println!("-h --help\t Usage");
}

fn main() {
    let args: Vec<String> = os::args();
    let program = args[0].clone();

    let opts = [
        optopt("o", "", "set output filename", "NAME"),
        optopt("p", "production-rate", "set production rate of central source", "PROD_RATE"),
        optopt("s", "size", "maximum allowable x and y value in the box", "SIZE"),
        optopt("n", "nodes", "number of nodes in the box", "NODES"),
        optopt("d", "sinks", "number of sinks in the box", "SINKS"),
        optflag("h", "help", "print this help menu")
    ];
    let matches = match getopts(args.tail(), opts) {
        Ok(m) => { m }
        Err(f) => { panic!(f.to_string()) }
    };
    //Print help, if needed
    if matches.opt_present("h") {
        print_usage(program.as_slice(), opts);
        return;
    }
    let prod_rate = match matches.opt_str("p") {
        None => { 100 }
        Some(x) => { 
            match from_str(x.as_slice()) {
                Some(y) => { y }
                None => { panic!("Production rate argument, '-p', is not an integer"); }
            }
        }
    };
    let size : f64 = match matches.opt_str("s") {
        None => { 10.0 }
        Some(x) => { 
            match from_str(x.as_slice()) {
                Some(y) => { y }
                None => { panic!("Size argument, '-s', is not a number"); }
            }
        }
    };
    let nodes : uint = match matches.opt_str("n") {
        None => { 50 }
        Some(x) => {
            match from_str(x.as_slice()) {
                Some(y) => { y }
                None => { panic!("Argument for number of nodes, '-n', is not an integer"); }
            }
        }
    };
    let sinks : uint = match matches.opt_str("d") {
        None => { 4 }
        Some(x) => {
            match from_str(x.as_slice()) {
                Some(y) => { y }
                None => { panic!("Argument for number of sinks, '-d', is not an integer"); }
            }
        }
    };
    let output: Box<Writer> = match matches.opt_str("o") {
        None => { box std::io::stdio::stdout() as Box<Writer> }
        Some(filename) => { box File::create(&Path::new(filename)).unwrap() as Box<Writer> }
    };

    gen_matrix(size, prod_rate, nodes, sinks, output);
}
