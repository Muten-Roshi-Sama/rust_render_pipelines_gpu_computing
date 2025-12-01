mod cube_app;
mod textured_cube_app;

use std::sync::Arc;

use crate::textured_cube_app::TexturedCubeApp;
use wgpu_bootstrap::{egui, Runner};

/*
    Physics 
        1. CubeApp : Colored cube
        2. TexturedCubeApp : Textured Cube + Differential Light effect.
        3. TexturedGlobeSpecular : Textured Globe using Specular Light reflection.
        


*/



fn main() {

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