
import aexlo from "aexlo";

const instance = new aexlo.PluginInstance ("D:\\Projects\\Development\\Node\\aexlo.js\\lib\\test\\SDK_Noise.aex");
console.log (instance.about());
console.log (instance.setupGlobal());
console.log (instance.setupParameters());
console.log (instance.render());

//DONE: About
//DONE: Global Setup
//DONE: Params Setup
//DONE: Render
//TODO: Smart Pre Render
//TODO: Smart Render
// aexlo.loadAEX("D:\\Projects\\Development\\Node\\aexlo.js\\lib\\test\\SDK_Noise.aex"); // null
