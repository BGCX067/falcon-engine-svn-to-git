class 'FalconTestApp' (BaseApp)

function FalconTestApp:__init(name) --constructor
    BaseApp.__init(self, name)
end

function FalconTestApp:Load()

	spaceSkyBox = SkyBox("./data/images/skybox.dds")
	spaceSkyBox:Init(self.resourceManager)
	self.scene:SetSkyBox(spaceSkyBox)

	crate = Crate()
	crate:Init(self.resourceManager)
	self.scene:AttachChild(crate)

	for i=1,10,1 do
		for j=1,10,1 do 
			box = Box()
			box:SetTranslate(Vec3(10-(i*2),-2,10-(j*2)));
			box:Init(self.resourceManager)
			self.scene:AttachChild(box)
		end
	end

	myMenu = Menu()
	myMenu:Init(self.resourceManager)

	myGround = Ground()
	myGround:Init(self.resourceManager)
	self.scene:AttachChild(myGround)

end
