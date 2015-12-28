class 'Ground' (GameObject)

-- Crate inheriting from GameObject
	function Ground:__init() -- constructor
		GameObject.__init(self)
	end

	function Ground:Init(resmgr)
		--initial position
		self:SetTranslate(Vec3(0,-5,0))
		
		resmgr:GetMesh("./data/models/ground.obj", self);
		-- Add a shader
		self.shader = resmgr.GetShader(resmgr, "DiffuseTexture");
		--add physics
		self.physicsObject = PhysicsBox(0, Vec3(25,0.5,25));
		self.physicsObject:Init(self);
		
		-- Create & set TextureData
--~ 		temp = ShaderData();
--~ 		temp.color = Vec3(1,0,0);
--~ 		self.SetShaderData(temp);
		self.shaderData = ShaderData();
		self.shaderData.texture = resmgr:GetTexture("./data/images/ground.jpg")
	end
