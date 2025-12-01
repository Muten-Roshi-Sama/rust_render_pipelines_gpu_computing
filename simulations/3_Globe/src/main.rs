// main.rs
mod globe;


use std::sync::Arc;
mod sphere_vertices; // module to compute sphere geometry (vertices & indices)


use crate::globe::SphereApp;
use wgpu_bootstrap::{egui, Runner};

/*
    Physics Engine :
        3. TexturedGlobeSpecular : Textured Globe using Specular Light reflection.
*/

fn main() {

    let mut runner = Runner::new(
        "Globe",
        800,
        600,
        egui::Color32::from_rgb(245, 245, 245),
        32,
        0,
        Box::new(|context| Arc::new(SphereApp::new(context))),
    );



    runner.run();
}