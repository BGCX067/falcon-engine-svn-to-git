require 'Game/FalconTestApp'
require 'Game/Crate'
require 'Game/Box'
require 'Game/Ground'
require 'Game/Menu'
require 'Game/Utils/TypeDefs'

collectgarbage("stop")

app = FalconTestApp("Falcon Test Application");

if app:Create() then
	--load our content
	app:Load()
	--run the game
	app:Run()
end
