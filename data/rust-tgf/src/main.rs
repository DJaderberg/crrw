extern crate getopts;
use getopts::{optopt,optflag,getopts,OptGroup};
use std::os;
use std::io::fs::File;
use std::rand;

//Since this is still for the alpha, there's a lot of unstable stuff that is 
//still used
#[allow(unstable)]
fn gen_matrix(size: f64, prod_rate: i64, nodes: u64, sinks: u64, mut out: Box<Writer>) {
    //Define Nodes (id, x-pos, y-pos, opt. production rate)
    let sqrt_nodes : f64 = std::num::Float::sqrt(nodes as f64);
    let mut i_range = 0u64..(sqrt_nodes as u64);
    match out.write((nodes.to_string() + "\n").as_bytes()) {
        Ok(()) => (),
        Err(e) => panic!(e.desc)
    };
    for i in i_range {
        let mut j_range = 0u64..(sqrt_nodes as u64);
        for j in j_range {
            let x_val = (i as f64)*size/sqrt_nodes + 0.3*size/sqrt_nodes*(rand::random::<f64>() - 0.5) + (if i%2 == 0 { 0.0 } else { 0.0 });
            let y_val = (j as f64)*size/sqrt_nodes + 0.3*size/sqrt_nodes*(rand::random::<f64>() - 0.5) + (if i%2 == 0 { 0.0 } else { size/sqrt_nodes*0.5 });
            let mut output : String = (i*(sqrt_nodes as u64)+j).to_string() + " " + x_val.to_string().as_slice() + " " + y_val.to_string().as_slice();
            if i as u64 <= sinks {
                output = output + " ";
            }
            //If Source
            if i+j==0 {
                output = output + prod_rate.to_string().as_slice();
                //If Sink
            } else if i==0 && (i+j) as u64 <= sinks {
                output = output + "-" + (prod_rate/sinks as i64).to_string().as_slice();
            }
            output = output + "\n";
            match out.write(output.as_bytes()) {
                Ok(()) => (),
                Err(e) => panic!(e.desc)
            };
        }
    }
    return;
}

fn print_usage(program: &str, _opts: &[OptGroup]) {
    println!("Usage: {} [options]", program);
    println!("-o\t\tOutput filename");
    println!("-p\t\tProduction rate of central source");
    println!("-n\t\tNumber of Nodes");
    println!("-s\t\tMaximum allowable x and y value in the box");
    println!("-d\t\tNumber of sinks");
    println!("-h --help\t Usage");
}


//Since this is still for the alpha, there's a lot of unstable stuff that is 
//still used
#[allow(unstable)]
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
    let matches = match getopts(args.tail(), &opts) {
        Ok(m) => { m }
        Err(f) => { panic!(f.to_string()) }
    };
    //Print help, if needed
    if matches.opt_present("h") {
        print_usage(program.as_slice(), &opts);
        return;
    }
    let prod_rate = match matches.opt_str("p") {
        None => { 100 }
        Some(x) => { 
            match x.parse::<i64>() {
                Some(y) => { y }
                None => { panic!("Production rate argument, '-p', is not an integer"); }
            }
        }
    };
    let size : f64 = match matches.opt_str("s") {
        None => { 10.0 }
        Some(x) => { 
            match x.parse::<f64>() {
                Some(y) => { y }
                None => { panic!("Size argument, '-s', is not a number"); }
            }
        }
    };
    let nodes : u64 = match matches.opt_str("n") {
        None => { 50 }
        Some(x) => {
            match x.parse::<u64>() {
                Some(y) => { y }
                None => { panic!("Argument for number of nodes, '-n', is not an integer"); }
            }
        }
    };
    let sinks : u64 = match matches.opt_str("d") {
        None => { 4 }
        Some(x) => {
            match x.parse::<u64>() {
                Some(y) => { y }
                None => { panic!("Argument for number of sinks, '-d', is not an integer"); }
            }
        }
    };
    let output: Box<Writer> = match matches.opt_str("o") {
        None => { Box::new(std::io::stdio::stdout()) as Box<Writer> }
        Some(filename) => { Box::new(File::create(&Path::new(filename)).unwrap()) as Box<Writer> }
    };

    gen_matrix(size, prod_rate, nodes, sinks, output);
}
