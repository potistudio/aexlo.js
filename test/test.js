
import fs from "node:fs";
import path from "node:path";
import aexlo from "aexlo";
import { Canvas } from "canvas";

const AE_PLUGIN_DIRECTORY = "C:/Program Files/Adobe/Adobe After Effects 2025/Support Files/Plug-ins/Effects";
const PROJECT_PLUGIN_DIRECTORY = "D:/Projects/Development/Node/aexlo.js/test/plugins";
const PLUGIN_NAME = "SDK_Noise.aex"
const instance = new aexlo.PluginInstance (path.resolve(PROJECT_PLUGIN_DIRECTORY, PLUGIN_NAME));

const WIDTH = 1920;
const HEIGHT = 1080;

loadResources();
invokePlugin();

function loadResources() {
	const resources = instance.loadResources();
	const kind = resources.split("MIB8dnik")[1].split("MIB8eman")[0];
	const name = resources.split("MIB8eman")[1].split("MIB8gtac")[0];
	const category = resources.split("MIB8gtac")[1].split("MIB84668")[0];
	const entry = resources.split("MIB84668")[1].split("MIB8RVPe")[0];
	const ripl = resources.split("MIB8RVPe")[1];
	const match = resources.split ("MIB8ANMe")[1].split ("MIB8LFea")[0];
	const url = resources.split ("MIB8LRUe")[1];

	console.log (`kind: ${kind}
	name: ${name}
	category: ${category}
	matchName: ${match}
	url: ${url}`);
}

function invokePlugin() {
	instance.about();
	console.log (instance.setupParameters());
	console.log (instance.getCurrentParameters());

	instance.setResolution (WIDTH, HEIGHT);

	console.log ("\n -------- set parameter to \"10\" (default) -------- ")
	render (10);

	console.log ("\n -------- set parameter to \"20\" -------- ")
	instance.setParameterById (1, 20);
	render (20);

	console.log ("\n -------- set parameter to \"50\" -------- ")
	instance.setParameterById (1, 50);
	render (50);

	console.log ("\n -------- set parameter to \"100\" -------- ")
	instance.setParameterById (1, 100);
	render (100);

	// console.log ("\n -------- set parameter to \"0\" -------- ")
	// instance.setParameterById (1, 0);
	// instance.render();
}

function render (index) {
	const canvas = new Canvas (WIDTH, HEIGHT);
	const context = canvas.getContext ("2d");
	const imageData = context.createImageData (WIDTH, HEIGHT);

	const rendered_pixels = instance.render();

	for (let i = 0; i < rendered_pixels.length / 4; i++) {
		const pixelOffset = i * 4;

		imageData.data[pixelOffset] = rendered_pixels[pixelOffset];
		imageData.data[pixelOffset + 1] = rendered_pixels[pixelOffset + 1];
		imageData.data[pixelOffset + 2] = rendered_pixels[pixelOffset + 2];
		imageData.data[pixelOffset + 3] = rendered_pixels[pixelOffset + 3];
	}

	context.putImageData (imageData, 0, 0);
	fs.writeFileSync (path.resolve(`output_${index}.png`), canvas.toBuffer ("image/png"));
}
