export class PluginInstance {
	constructor();
	loadResources(): string;
	about(): number;
	setupGlobal(): number;
	setupSequence(): number;
	setupParameters(): number;
	render(): number;
	smartPreRender(): number;
	smartRender(): number;
}
