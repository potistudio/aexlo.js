
#include <napi.h>
#include <iostream>
#include <windows.h>
#include "AEXDef.h"

typedef struct PF_Iterate8Suite2 {
	PF_Err (*iterate) (
		PF_InData		*in_data,
		A_long			progress_base,
		A_long			progress_final,
		PF_EffectWorld	*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		void			*refcon,
		PF_Err(*pix_fn)(void* refcon, A_long x, A_long y, PF_Pixel* in, PF_Pixel* out),
		PF_EffectWorld	*dst
	);


	PF_Err(*iterate_origin)(
		PF_InData		*in_data,
		A_long			progress_base,
		A_long			progress_final,
		PF_EffectWorld	*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		const PF_Point	*origin,
		void			*refcon,
		PF_Err(*pix_fn)(void* refcon, A_long x, A_long y, PF_Pixel* in, PF_Pixel* out),
		PF_EffectWorld	*dst);

	PF_Err(*iterate_lut)(
		PF_InData		*in_data,
		A_long			progress_base,
		A_long			progress_final,
		PF_EffectWorld	*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		A_u_char		*a_lut0,		/* pass NULL for identity */
		A_u_char		*r_lut0,		/* pass NULL for identity */
		A_u_char		*g_lut0,		/* pass NULL for identity */
		A_u_char		*b_lut0,		/* pass NULL for identity */
		PF_EffectWorld	*dst);

	PF_Err(*iterate_origin_non_clip_src)(
		PF_InData		*in_data,
		A_long			progress_base,
		A_long			progress_final,
		PF_EffectWorld	*src,
		const PF_Rect	*area,
		const PF_Point	*origin,
		void			*refcon,
		PF_Err(*pix_fn)(void* refcon, A_long x, A_long y, PF_Pixel* in, PF_Pixel* out),
		PF_EffectWorld	*dst);

	PF_Err(*iterate_generic)(
		A_long			iterationsL,	/* >> */		// can be PF_Iterations_ONCE_PER_PROCESSOR
		void			*refconPV,		/* >> */
		PF_Err(*fn_func)(
			void	*refconPV,			/* >> */
			A_long	thread_indexL,		// only call abort and progress from thread_indexL == 0.
			A_long	i,
			A_long	iterationsL));		// never sends PF_Iterations_ONCE_PER_PROCESSOR

} PF_Iterate8Suite2;

typedef struct PF_WorldTransformSuite1 {
	PF_Err (*composite_rect) (
		PF_ProgPtr     effect_ref,  /* from in_data */
		PF_Rect        *src_rect,   /* rectangle in source image */
		A_long         src_opacity, /* opacity of src */
		PF_EffectWorld *source_wld, /* src PF world */
		A_long         dest_x,      /* upper left-hand corner of src rect...*/
		A_long         dest_y,      /* ... in composite image */
		PF_Field       field_rdr,   /* which scanlines to render (all, upper, lower) */
		PF_XferMode    xfer_mode,   /* Copy, Composite Behind, Composite In Front */
		PF_EffectWorld *dest_wld   /* Destination buffer. Already filled */
	);

	PF_Err (*blend) (
		PF_ProgPtr           effect_ref,		/* reference from in_data */
		const PF_EffectWorld *src1,
		const PF_EffectWorld *src2,
		PF_Fixed             ratio,			/* 0 == full src1, 0x00010000 == full src2 */
		PF_EffectWorld       *dst
	);

	PF_Err (*convolve) (
		PF_ProgPtr     effect_ref,  /* reference from in_data */
		PF_EffectWorld *src,
		const PF_Rect  *area,       /* pass NULL for all pixels */
		PF_KernelFlags flags,
		A_long         kernel_size,
		void           *a_kernel,
		void           *r_kernel,
		void           *g_kernel,
		void           *b_kernel,
		PF_EffectWorld *dst
	);

	PF_Err (*copy) (
		PF_ProgPtr     effect_ref, /* reference from in_data */
		PF_EffectWorld *src,
		PF_EffectWorld *dst,
		PF_Rect        *src_r,     /* pass NULL for whole world */
		PF_Rect        *dst_r     /* pass NULL for whole world */
	);

	PF_Err (*copy_hq) (
		PF_ProgPtr     effect_ref, /* reference from in_data */
		PF_EffectWorld *src,
		PF_EffectWorld *dst,
		PF_Rect        *src_r,     /* pass NULL for whole world */
		PF_Rect        *dst_r     /* pass NULL for whole world */
	);


	 PF_Err	(*transfer_rect)(
		PF_ProgPtr				effect_ref,
		PF_Quality				quality,
		PF_ModeFlags			m_flags,
		PF_Field				field,
		const PF_Rect			*src_rec,
		const PF_EffectWorld	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		A_long					dest_x,
		A_long					dest_y,
		PF_EffectWorld			*dst_world);

	 PF_Err	(*transform_world)(
		PF_ProgPtr				effect_ref,
		PF_Quality				quality,
		PF_ModeFlags			m_flags,
		PF_Field				field,
		const PF_EffectWorld	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		const PF_FloatMatrix	*matrices,
		A_long					num_matrices,
		PF_Boolean				src2dst_matrix,
		const PF_Rect			*dest_rect,
		PF_EffectWorld			*dst_world);
} PF_WorldTransformSuite1;

class AEXLoaderWrapper : public Napi::ObjectWrap<AEXLoaderWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "AEXLoader", {
				InstanceMethod ("load", &AEXLoaderWrapper::Load)
			});
			Napi::FunctionReference *constructor = new Napi::FunctionReference();
			*constructor = Napi::Persistent (func);

			env.SetInstanceData<Napi::FunctionReference>(constructor);
			exports.Set ("AEXLoader", func);

			return exports;
		}

		AEXLoaderWrapper (const Napi::CallbackInfo &info) : Napi::ObjectWrap<AEXLoaderWrapper> (info) {
			// Constructor
			Napi::Env env = info.Env();
		}

	private:
		Napi::Value Load (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();
			return env.Null();
		}
};

PF_Err addParam (PF_ProgPtr effect_ref, PF_ParamIndex index, PF_ParamDefPtr def) {
	std::cout << "Param Type: " << def->param_type << std::endl;
	std::cout << "Param Name: " << def->name << std::endl;
	std::cout << "Valid Min: " << def->u.fs_d.valid_min << std::endl;
	std::cout << "Slider Min: " << def->u.fs_d.slider_min << std::endl;
	std::cout << "Valid Max: " << def->u.fs_d.valid_max << std::endl;
	std::cout << "Slider Max: " << def->u.fs_d.slider_max << std::endl;
	std::cout << "Value: " << def->u.fs_d.value << std::endl;
	std::cout << "Default: " << def->u.fs_d.dephault << std::endl;
	std::cout << "Precision: " << def->u.fs_d.precision << std::endl;
	std::cout << "Display Flags: " << def->u.fs_d.display_flags << std::endl;
	std::cout << "Flags: " << def->u.fs_d.fs_flags << std::endl;
	std::cout << "Curve Tolerance: " << def->u.fs_d.curve_tolerance << std::endl;
	std::cout << "ID: " << def->uu.id << std::endl;
	return PF_Err_NONE;
}

PF_Err iterate (PF_InData *in_data, A_long progress_base, A_long progress_final, PF_EffectWorld *src, const PF_Rect *area, void *refcon, PF_Err(*pix_fn)(void* refcon, A_long x, A_long y, PF_Pixel* in, PF_Pixel* out), PF_EffectWorld *dts) {
	std::cout << "iterate" << std::endl;

	PF_Pixel8 *inPixel = new PF_Pixel8();
	inPixel->alpha = 255;

	PF_Pixel8 *outPixel = new PF_Pixel8();

	pix_fn (refcon, 0, 0, inPixel, outPixel);

	std::cout << (int)outPixel->blue << std::endl;

	return 0;
}

PF_Err copy (PF_ProgPtr effect_ref, PF_EffectWorld *src, PF_EffectWorld *dst, PF_Rect *src_r, PF_Rect *dst_r) {
	std::cout << "copy" << src << std::endl;
	return 0;
}

SPErr acquireSuite (const char *name, int32 version, const void **suite) {
	std::cout << "Acquiring Suite: " << name << " Version: " << version << std::endl;

	if (strcmp(name, "PF Iterate8 Suite") == 0) {
		PF_Iterate8Suite2 *i8s = new PF_Iterate8Suite2();
		i8s->iterate = &iterate;
		*suite = i8s;

		return 0;
	} else if (strcmp(name, "PF World Transform Suite") == 0) {
		PF_WorldTransformSuite1 *wts = new PF_WorldTransformSuite1();
		wts->copy = &copy;
		*suite = wts;

		return 0;
	}

	return -1; // Error
}

SPErr releaseSuite (const char *name, int32 version) {
	std::cout << "Releasing Suite: " << name << " Version: " << version << std::endl;
	return 0;
}

class AEXPlugin {
	public:
		// "HINSTANCE" is the handle to the loaded library
		HINSTANCE module;
		EntryPointFunc entry;

		AEXPlugin (std::string path) {
			this->module = LoadLibrary (path.c_str());
			if (this->module == NULL) {
				throw std::runtime_error ("Failed to load AEX");
			}

			// Cast the exported function address "EffectMain" or "EntryPointFunc" to a function pointer
			this->entry = (EntryPointFunc)GetProcAddress (module, "EffectMain");
			if (this->entry == NULL) {
				this->entry = (EntryPointFunc)GetProcAddress (module, "EntryPointFunc");
				if (this->entry == NULL)
					throw std::runtime_error ("Failed to load AEX");
			}
		}

		~AEXPlugin () {
			if (this->module != NULL) {
				FreeLibrary (this->module);
			}
		}

		PF_Err Execute (PF_Cmd cmd, PF_InData *inData, PF_OutData *outData, PF_ParamDef *params[], PF_LayerDef *layer) {
			PF_Err err = PF_Err_NONE;

			err = this->entry (cmd, inData, outData, params, layer, NULL);

			return err;
		}

		PF_Err ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *layer) {
			PF_Err error = PF_Err_NONE;

			const int CMD = PF_Cmd_ABOUT;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			return error;
		}

		PF_Err ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *layer) {
			PF_Err error = PF_Err_NONE;

			const int CMD = PF_Cmd_GLOBAL_SETUP;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "\n-------- begin Global Setup --------\n" << std::endl;

			std::cout << "Version: " << out_data->my_version << std::endl;
			std::cout << "Flags: " << out_data->out_flags << std::endl;
			std::cout << "Flags2: " << out_data->out_flags2 << std::endl;

			std::cout << "\n-------- end Global Setup --------\n" << std::endl;

			return error;
		}

		PF_Err ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *layer) {
			const int CMD = PF_Cmd_PARAMS_SETUP;
			PF_Err error = PF_Err_NONE;

			/* Arguments Setup */
			in_data->inter = PF_InteractCallbacks();
			in_data->inter.add_param = &addParam;

			/* Execute */
			std::cout << "\n-------- begin Parameters Setup --------\n" << std::endl;

			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << out_data->num_params << std::endl;

			std::cout << "\n-------- end Parameters Setup --------\n" << std::endl;

			return error;
		}

		PF_Err ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *layer) {
			const int CMD = PF_Cmd_RENDER;

			PF_Err error = PF_Err_NONE;
			in_data->pica_basicP = new SPBasicSuite();
			in_data->pica_basicP->AcquireSuite = &acquireSuite;
			in_data->pica_basicP->ReleaseSuite = &releaseSuite;

			params[1] = new PF_ParamDef();
			error = this->Execute (CMD, in_data, out_data, params, layer);

			// const void *suiteP;
			// NoiseInfo niP;
			// niP.valF = params[1]->u.fs_d.value;
			// in_data->pica_basicP->AcquireSuite ("PF Iterate8 Suite", 1, &suiteP);
			// const PF_Iterate8Suite2 *i_suiteP = reinterpret_cast<const PF_Iterate8Suite2*>(suiteP);
			// i_suiteP->iterate (in_data, 0, 0, &params[1]->u.ld, NULL, (void*)&niP, FI, layer);

			return error;
		}
};

int sprintf_m (A_char *buffer, const A_char *format, ...) {
	va_list args;
	va_start (args, format);

	std::cout << "\n-------- begin About --------\n" << std::endl;

	vsnprintf (buffer, 1024, format, args); // format
	std::cout << buffer << std::endl; // content

	std::cout << "\n-------- end About --------\n" << std::endl;

	va_end (args);
	return 0;
};

// Main
class Aexlo : public Napi::Addon<Aexlo> {
	public:
		Aexlo (Napi::Env env, Napi::Object exports) {
			DefineAddon (exports, {
				InstanceMethod ("loadAEX", &Aexlo::LoadAEX)
			});

			AEXLoaderWrapper::Init (env, exports);
		}

	private:
		Napi::Value LoadAEX (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			//* Validate Arguments
			if (info.Length() != 1) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			if (!info[0].IsString()) {
				Napi::TypeError::New (env, "Wrong argument type").ThrowAsJavaScriptException();
				return env.Null();
			}

			std::string path = info[0].As<Napi::String>();

			//* Initialize Data
			PF_Cmd cmd = PF_Cmd_GLOBAL_SETUP;
			PF_InData* inData = new PF_InData();
			PF_OutData* outData = new PF_OutData();
			PF_ParamDef* params[1] = {};
			PF_LayerDef* layer = new PF_LayerDef();

			inData->utils = new _PF_UtilCallbacks();
			inData->utils->ansi = PF_ANSICallbacks();
			inData->utils->ansi.sprintf = &sprintf_m;
			// inData->pica_basicP = new SPBasicSuite();
			// inData->pica_basicP->AcquireSuite = &AcquireSuite;

			//* Load Plugin
			AEXPlugin* plugin;
			try {
				plugin = new AEXPlugin (path);
			} catch (...) {
				Napi::Error::New (env, "Failed to load AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			//* Execute Plugin (test)
			try {
				PF_Err err = PF_Err_NONE;
				err = plugin->ExecuteGlobalSetup (inData, outData, params, layer);
				err = plugin->ExecuteParamsSetup (inData, outData, params, layer);
				err = plugin->ExecuteRender (inData, outData, params, layer);
				std::cout << err << std::endl; // Expect 0
			} catch (...) {
				Napi::Error::New (env, "Failed to execute AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			return env.Null();
		}
};

NODE_API_ADDON (Aexlo);
