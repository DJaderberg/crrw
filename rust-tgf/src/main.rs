extern crate getopts;
use getopts::{optopt,optflag,getopts,OptGroup};
use std::os;
use std::io::fs::File;

fn gen_matrix(size: uint, prod_rate: int, mut out: Box<Writer>) {
    //Define Nodes (id, x-pos, y-pos, opt. production rate)
    let mut y_range = std::iter::range(0u, size);
    for y in y_range {
        let mut x_range = std::iter::range(0u, size);
        for x in x_range {
            //Node id
            out.write((y*size + x).to_string().as_bytes());
            out.write(b" ");
            //x position
            out.write(x.to_string().as_bytes());
            out.write(b".0 ");
            //y position
            out.write(y.to_string().as_bytes());
            out.write(b".0");
            //If Sink
            if ((x==0 && y==0) || (x==0 && y==size-1) || 
                (x==size-1 && y == 0) || (x==size-1 && y==size-1)) {
                out.write(b" -1");
            //If Source
            } else if (x==size/2+2 && y==size/2+1) {
                out.write(b" ");
                out.write(prod_rate.to_string().as_bytes());
            }
            out.write(b"\n");
        }
    }
    //Separator
    out.write(b"#\n");
    //Define all Edges (to, from)
    let mut id_range = std::iter::range(0, size*size);
    for id in id_range {
        //Up
        if (id > size) {
            out.write(id.to_string().as_bytes());
            out.write(b" ");
            out.write((id-size).to_string().as_bytes());
            out.write(b"\n");
        }
        //Down
        if (id+size < size*size) {
            out.write(id.to_string().as_bytes());
            out.write(b" ");
            out.write((id+size).to_string().as_bytes());
            out.write(b"\n");
        }
        //Left
        if (id%size > 0) {
            out.write(id.to_string().as_bytes());
            out.write(b" ");
            out.write((id-1).to_string().as_bytes());
            out.write(b"\n");
        }
        //Right
        if (id%size < size-1) {
            out.write(id.to_string().as_bytes());
            out.write(b" ");
            out.write((id+1).to_string().as_bytes());
            out.write(b"\n");
        }
    }
    return;
}

fn print_usage(program: &str, _opts: &[OptGroup]) {
    println!("Usage: {} [options]", program);
    println!("-o\t\tOutput filename");
    println!("-p\t\tProduction rate of central source");
    println!("-h --help\t Usage");
}

fn main() {
    let args: Vec<String> = os::args();
    let program = args[0].clone();

    let opts = [
        optopt("o", "", "set output filename", "NAME"),
        optopt("p", "production-rate", "set production rate of central source", "PROD_RATE"),
        optopt("s", "size", "number of nodes along one edge of the matrix", "SIZE"),
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
    let size : uint = match matches.opt_str("s") {
        None => { 10 }
        Some(x) => { 
            match from_str(x.as_slice()) {
                Some(y) => { y }
                None => { panic!("Size argument, '-s', is not an integer"); }
            }
        }
    };
    let output: Box<Writer> = match matches.opt_str("o") {
        None => { box std::io::stdio::stdout() as Box<Writer> }
        Some(filename) => { box File::create(&Path::new(filename)).unwrap() as Box<Writer> }
    };

    gen_matrix(size, prod_rate, output);
}
