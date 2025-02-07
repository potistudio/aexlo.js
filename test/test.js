
import path from "node:path";
import aexlo from "aexlo";

const AE_PLUGIN_DIRECTORY = "C:/Program Files/Adobe/Adobe After Effects 2025/Support Files/Plug-ins/Effects";
const PROJECT_PLUGIN_DIRECTORY = "D:/Projects/Development/Node/aexlo.js/test/plugins";
const PLUGIN_NAME = "Rand_Pos.aex"
const instance = new aexlo.PluginInstance (path.resolve(PROJECT_PLUGIN_DIRECTORY, PLUGIN_NAME));
const instance2 = new aexlo.PluginInstance (path.resolve(PROJECT_PLUGIN_DIRECTORY, "SDK_Noise.aex"));

loadResources();
executeAll();

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

function executeAll() {
	// console.log (instance.about());
	// console.log (instance.setupGlobal());
	console.log (instance.setupParameters());
	instance2.setupParameters();
	// console.log (instance.render());
	// console.log (instance.smartRender());
}
