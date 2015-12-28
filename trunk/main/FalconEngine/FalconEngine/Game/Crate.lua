class 'Crate' (GameObject)

printer = DebugPrinter();

-- Crate inheriting from GameObject
	function Crate:__init() -- constructor
		GameObject.__init(self)
	end

	function Crate:Init(resmgr)
		printer.printString(printer, "Initializing Crate")

		resmgr:GetMesh("./data/models/cube.obj", self);

		printer.printMesh(printer, self.mesh);
		-- Add a shader
		self.shader = resmgr:GetShader("DiffuseTexture");
		
		self.physicsObject = PhysicsBox(100, Vec3(0.5,0.5,0.5));
		self.physicsObject:Init(self);
		-- Create & set TextureData
		self.shaderData = ShaderData();
		self.shaderData.texture = resmgr:GetTexture("./data/images/crate-diffuse.png")
		
	end

	function Crate:Update(inputState)
	
		if inputState:IsKeyDown(Key_LEFT) == true then
			self.AddForce(self, Vec3(1000,0,0))
		end

		if inputState:IsKeyDown(Key_RIGHT) == true then
			self:AddForce(Vec3(-1000,0,0))
		end
		
		if inputState:IsKeyDown(Key_UP) == true then
			self:AddForce(Vec3(0,0,-1000))
		end
		
		if inputState:IsKeyDown(Key_DOWN) == true then
			self:AddForce(Vec3(0,0,1000))
		end
	end
