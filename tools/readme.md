# generating GPU traces

1. take a look in ocelot_installation_guide : use docker image which has the correct nvcc version and gpuocelot installed

2. when the docker container is properly set up, copy the library binaries from /usr/local/lib
  - should copy ```libocelot.so```, ```libocelotTrace.so```, ```libocelotTrace.a``` to ./macsim/tools

3. add a configure.ocelot script to ./macsim/tools
  - need to add x86Trace: true

```{json}
{
	ocelot: "ocelot",
	trace: { 
		database: "traces-ipdom/database.trace",
		memoryChecker: {
			enabled: true,
			checkInitialization: false
		},
		raceDetector: {
			enabled: true,
			ignoreIrrelevantWrites: true
		},
		debugger: {
			enabled: false,
			kernelFilter: "_Z13scalarProdGPUPfS_S_ii",
			alwaysAttach: true
		},
		cacheSimulator: {
			enabled: false,
		},
		branch: false,
		memory: false,
    x86Trace: true
	},
	cuda: {
		implementation: CudaRuntime,
		runtimeApiTrace: "trace/CudaAPI.trace"
	},
	executive: {
		devices: [ emulated ],
		asynchronousKernelLaunch: true,
		port: 2011,
		host: "127.0.0.1",
		optimizationLevel: none,
		workerThreadLimit: 1,
		reconvergenceMechanism: "ipdom",
		warpSize: 1
	},
	optimizations: {
		subkernelSize: 1000,
		simplifyCFG: true,
		hoistSpecialValues: false
	},
	checkpoint: {
		enabled: false,
		path: "./",
		prefix: "TestCudaIndirectFunctionCall_",
		suffix: ".checkpoint"
	}
}
```

4. link the sourcefile.cu with the gpuocelot libraries
  - ```nvcc sourcefile.cu –locelot –ocelotTrace -arch=sm_20```
  - this will generate ```a.out``` file

5. set up the evironment variables
  - export COMPUTE_VERSION="2.0"
  - export KERNEL_INFO_PATH="kernel_info"

6. generate traces
  - ./gpu_tracegen.py -cmd=./a.out
