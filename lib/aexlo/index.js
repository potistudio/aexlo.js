import bindings from "bindings";
const addon = bindings("aexlo");

class PluginInstance {
	addon;
	defaultParameters = [];
	currentParameters = [];

	constructor (path) {
		this.addon = new addon.PluginInstance (path);
	}

	about() {
		return this.addon.about();
	}

	setupGlobal() {
		return this.addon.setupGlobal();
	}

	setupSequence() {
		return this.addon.setupSequence();
	}

	setupParameters() {
		const error = this.addon.setupParameters();
		this.defaultParameters = this.addon.getParameters();
		this.currentParameters = this.defaultParameters;

		return error;
	}

	render() {
		return this.addon.render ({ width: 1000, height: 1000 }, this.getCurrentParameters());
	}

	smartPreRender() {
		return this.addon.smartPreRender();
	}

	smartRender() {
		return this.addon.smartRender();
	}

	getCurrentParameters() {
		return this.currentParameters;
	}

	setParameterById (id, value) {
		this.currentParameters.find (p => p.id === id).value = value;
	}

	setParameterByName (name, value) {
		this.currentParameters.find (p => p.name === name).value = value;
	}

	loadResources() {
		return this.addon.loadResources();
	}
};

export default {
	PluginInstance
};
