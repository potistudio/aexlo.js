
import aexlo from "aexlo";

const instance = new aexlo.PluginInstance ("D:\\Projects\\Development\\Node\\aexlo.js\\lib\\test\\QCA3.aex");

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
// console.log (instance.about());
// console.log (instance.setupGlobal());
// console.log (instance.setupParameters());
// console.log (instance.render());

//DONE: About
//DONE: Global Setup
//DONE: Params Setup
//DONE: Render
//TODO: Smart Pre Render
//TODO: Smart Render
