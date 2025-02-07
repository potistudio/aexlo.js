export type parameter = {
	name: string;
	type: paramType;
};

export enum paramType {
	RESERVED       = -1,
	LAYER          = 0,
	SLIDER         = 2,
	FIX_SLIDER     = 3,
	ANGLE          = 4,
	CHECKBOX       = 5,
	COLOR          = 6,
	POINT          = 7,
	POPUP          = 8,
	CUSTOM         = 9,
	_NO_DATA       = 10,
	FLOAT_SLIDER   = 11,
	ARBITRARY_DATA = 12,
	PATH           = 13,
	GROUP_START    = 14,
	GROUP_END      = 15,
	BUTTON         = 16,
	RESERVED2      = 17,
	RESERVED3      = 18,
	POINT_3D       = 19,
};

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

	getParameters(): parameter[];
};
