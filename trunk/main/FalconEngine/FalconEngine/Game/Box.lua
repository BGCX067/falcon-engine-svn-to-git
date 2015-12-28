class 'Box' (GameObject)

printer = DebugPrinter();

-- Box inheriting from GameObject
	function Box:__init() -- constructor
		GameObject.__init(self)
	end

	function Box:Init(resmgr)
		resmgr:GetMesh("./data/models/cube.obj", self);

		-- Add a shader
		self.shader = resmgr:GetShader("BasicColor");
		
		self.physicsObject = PhysicsBox(5, Vec3(0.5,0.5,0.5));
		self.physicsObject:Init(self);

		self.shaderData = ShaderData();
		self.shaderData.color = Vec3(0.8,0.9,0.5)
		
	end
