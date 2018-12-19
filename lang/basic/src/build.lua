include("util/LLgen/build.lua")

llgen {
	name = "llgen",
	srcs = { "./*.g" }
}

normalrule {
	name = "tokentab_h",
	ins = {
		"./maketokentab",
		"util/cmisc+ed",
		matching(filenamesof("+llgen"), "/Lpars.h$"),
	},
	outleaves = { "tokentab.h" },
	commands = {
		"%{ins} %{outs}"
	}
}

cprogram {
	name = "em_bem",
	srcs = {
		"./*.c",
		matching(filenamesof("+llgen"), "%.c$"),
	},
	deps = {
		"./*.h",
		"+llgen",
		"+tokentab_h",
		"h+emheaders",
		"modules+headers",
		"modules/src/alloc+lib",
		"modules/src/em_code+lib_k",
		"modules/src/em_data+lib",
		"modules/src/em_mes+lib",
    "modules/src/read_em+lib_ev",
		"modules/src/print+lib",
		"modules/src/string+lib",
		"modules/src/system+lib",
	}
}

installable {
	name = "pkg",
	map = {
		["$(PLATDEP)/em_bem"] = "+em_bem"
	}
}

