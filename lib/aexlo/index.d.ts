export class PluginInstance {
	constructor();
	loadResources(): string;
	about(): number;
	setupGlobal(): number;
	setupParameters(): number;
	render(): number;
}
