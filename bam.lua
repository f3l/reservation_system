CheckVersion("0.4")

function Intermediate_Output(settings, input)
	return "objs/" .. string.sub(PathBase(input), string.len("src/")+1) .. settings.config_ext
end

function build(settings)
	settings.cc.Output = Intermediate_Output
	--SetDriversGCC(settings)
	--settings.cc.flags:Add("/EHsc")
	choose_compiler(settings)
	source = Collect("src/*.cpp")
	objects = Compile(settings, source)
	exe = Link(settings, "reservation_system", objects)
	return PseudoTarget(settings.config_name, exe)
end

function choose_compiler(settings)
	if ExecuteSilent("cl") == 0 then
		SetDriversCL(settings)
		settings.cc.flags:Add("/EHsc")
	elseif ExecuteSilent("g++ -v") == 0 then
		SetDriversGCC(settings)
		settings.cc.flags:Add("-Wall")
	elseif ExecuteSilent("clang -v") == 0 then
		SetDriversClang(settings)
		settings.cc.flags:Add("-Wall")
	else
		error("no c/c++ compiler found")
	end
end

-- Create the debug settings
debug_settings = NewSettings()
debug_settings.config_name = "debug"
debug_settings.config_ext = "_d"
debug_settings.debug = 1
debug_settings.optimize = 0
debug_settings.cc.defines:Add("CONF_DEBUG")

-- Create the release settings
release_settings = NewSettings()
release_settings.config_name = "release"
release_settings.config_ext = ""
release_settings.debug = 0
release_settings.optimize = 1
release_settings.cc.defines:Add("CONF_RELEASE")

release = build(release_settings)
debug = build(debug_settings)

