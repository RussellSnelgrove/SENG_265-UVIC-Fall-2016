#Russell Snelgrove
#due october 25

import re



class NotAChoice(Exception):

    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
        
class TooLarge(Exception):

    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
		
class format_265:
	def __init__(self, file):

	self.current ={
		'width':0,
		'new':False,
	}
	self.LW = 0
	self.LM = 0
	self.LS = 0
	self.FT = False
	strict
	self.inputlines = inputlines    
	self.display = []              
	self.editer1()
        
	self.commands = re.compile(r"\?(LS|LM|LW|FT) (\-|\+)?(\d+|on|off)\s*$")
	
	def editer1(self):
		for line in self.inputlines:
			result = self.parse(line)
			if result:
				self.display.extend([result])
     
	#This is my funcation for editing each line. It calls the global varibles and takes an input for a line
	def editer (self, line):
		tester = self.commands.match(line)
		if tester:
            coms = tester.groups()
            if coms[0] == "FT":
                if coms[2] == "on":
                    self.FT = True
                elif coms[2] == "off":
                    self.FT = False
                elif self.strict:
                    print coms
                    raise NotAChoice("Formatting has an error with the on/off. Line: " + line)
            # Otherwise we'll do operator based settings
            elif coms[1] == "+":
                try:
                    self.coms[0] = self.coms[0] + int(coms[2])
                except ValueError:
                    if self.strict:
                        raise ValueError("Passed an invalid value after the + sign, most specifically, you passed on/off to a non-?fmt sequence. Line: " + line)
            elif coms[1] == "-":
                try:
                    self.coms[0] = self.coms[0] - int(coms[2])
                except ValueError:
                    if self.strict:
                        raise ValueError("Passed an invalid value after the - sign, most specifically, you passed on/off to a non-?fmt sequence. Line: " + line)
            else:
                try:
                    self.coms[0] = int(coms[2])
                except ValueError:
                    if self.strict:
                        raise ValueError("Passed an invalid value after the control sequence, most specifically, you passed on/off to a non-?fmt sequence. Line: " + line)
            # Verify after each option change that the margins and LWs fit spec.
            if coms[0] == "LW":
                self.FT = True
            if self.LM < 0:
                if self.strict:
                    raise ValueError("The margins were less then 0, this is against spec. Line: " + line + ", Margin: " + str(self.LM) + ", Page Width: " + str(self.LW))
                self.LM = 0
            if self.LM > self.LW - 20:
                self.LM = self.LW - 20
                if self.LM < 0:
                    self.LM = 0
                if self.strict and self.LW > 20:
                    raise ValueError("The margins were greater then LW - 20, this is against spec. Line: " + line)
            line = None
	

	
        #If formating is on then this section will commit the required changes to the line else it will return the line
			if self.FT and line:
					segment = line.split()
					if segment == []:
							self.current['width'] = 0
							if self.current['new']:
									if self.LS ==0:
											return '\n'
									elif self.LS == 1:
											return '\n\n'
									elif self.LS ==2:
											return '\n\n\n'
							else:

									self.current['new'] = True
									if self.LS == 0:
											return '\n\n'
									elif self.LS ==1:
											return '\n\n\n'
									elif self.LS ==2:
											return '\n\n\n\n'


					self.current['new'] = False



					if self.current['width'] == 0:
							out = "".join( [" " for i in range(self.LM) ] )
							self.current['width'] = self.LM
					else:
							out = ""



					for word in segment:
					        if self.strict and len(word) > self.LW - self.LM:
									raise TooLarge("Your word size was too big to fit on a given line. Word: " + word)
							if self.current['width'] + len(word) >= self.LW:
									margin = "".join( [" " for i in range(self.LM) ] )
									if self.LS == 0:
											out = out + '\n' + margin
									elif self.LS ==1:
											out = out + '\n' + '\n' + margin
									elif self.LS ==2:
											out = out + '\n' + '\n' + '\n' + margin
									self.current['width'] = self.LM
							elif self.current['width'] != self.LM:
									self.current['width'] = self.current['width'] + 1
									out = out + ' '
							out = out + word
							self.current['width'] = self.current['width'] + len(word)
	
					return out
			else:
					return line
								
		def get_lines(self):
        return self.display



if __name__ == "__main__":
    resulter = format_265()
    lines = resulter.get_lines()
    print '\n'.join(lines)
