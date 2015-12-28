class 'MyButton' (Button)

-- MyButton inheriting from Button
	function MyButton:__init(x, y, width, height) -- constructor
		Button.__init(self, x, y, width, height)
	end
