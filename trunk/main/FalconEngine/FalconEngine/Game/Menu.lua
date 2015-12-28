class 'Menu' (Callable)

printer = DebugPrinter();
myButton = Button(0,0,250,100)

-- MainMenu inheriting from callable
	function Menu:__init() --constructor
			Callable.__init(self)
	end

	function Menu:Notify(callerPtr)
		printer:printString("Menu Has Been Notified!")
	end

	function Menu:Init(resmgr)
		myButton:Init()
		myButton.shader = resmgr:GetShader("BasicColor")
		myButton.shaderData = ShaderData()
		myButton.shaderData.color = Vec3(0,0,1)
		myButton:AddCallListener(self)

		resmgr:Add2DElement(myButton)
	end
