mod cube_app;
mod render_cube_textured;

use std::sync::Arc;

// use crate::cube_app::CubeApp;
use crate::render_cube_textured::TexturedCubeApp;
use wgpu_bootstrap::{egui, Runner};

fn main() {
    // Cube app
    // let mut runner = Runner::new(
    //     "Cube App",
    //     800,
    //     600,
    //     egui::Color32::from_rgb(245, 245, 245),
    //     32,
    //     0,
    //     Box::new(|context| Arc::new(CubeApp::new(context))),
    // );


    let mut runner = Runner::new(
        "Textured Cube",
        800,
        600,
        egui::Color32::from_rgb(245, 245, 245),
        32,
        0,
        Box::new(|context| Arc::new(TexturedCubeApp::new(context))),
    );



    runner.run();
}