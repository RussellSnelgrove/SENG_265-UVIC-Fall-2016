
import re
import inputfile



class Formatter:
	"A class for formatting input strings"
	def __init__(self, inputlines,none):
		
		self.coms = {'LW' = 0,'LM' = 0, 'FT' = False}
		self.LS
		self.newcheck = {'lineone' = False,'needsecond' = False}
		self.display = []
		self.temp = ""
		self.input  = inputfile.input()
		self.editer()


	def editer(self):
		counter = 0			# counter for checking if last line needs to be printed
		for line in self.input:
			counter = counter + 1
			# check if parameter
			com = re.match(r"\?(LS|LW|LM|FT) (\+|\-)?(\d+|on|off)",line)
			
			if com:		# go to parameter assignment function
				checker = com.groups()
				self.commands(checker)
			else:			# format the line because not parameter
				self.edit(line)
		# print last line if needed
		if counter !=1:
			if self.coms['FT'] == True and self.newcheck['lineone'] == False:
				self.display.extend([self.temp])
#====================================== Format Each Line



	def commands(self, checkie):	
	#= Does LW Option
		if checkie[0] == "LS":
			self.coms['LS'] = int(checkie[2])
		if checkie[0] == "LW":
			self.coms['LW'] = int(checkie[2])
			self.coms['FT'] = True
	#= Does LM Option
		if checkie[0] == "LM":
			if checkie[1]   == "+":
				self.coms['LM'] += int(checkie[2])
				if self.coms['LM'] > (self.coms['LW'] -20):
					self.coms['LM'] = self.coms['LW'] - 20
			# subtracts a value from existing margin
			elif checkie[1] == "-":
				self.coms['LM'] -= int(checkie[2])
				if self.coms['LM'] < 0:
					self.coms['LM'] = 0
			# assigns new value to margin
			else:
				self.coms['LM']   = int(checkie[2])
	#= Does FT Option
		if checkie[0]	 == "FT":

			# turns FT on
			if checkie[2]   == "on":
				self.coms['FT'] = True

			# turns FT off
			elif checkie[2] == "off":
				self.coms['FT'] = False


	def edit(self,line):
		temp2 = line[:]   #make copy to use if FT is off
		segments = line.split() # split line into list of segments
		#if formatting off, add basic line to display
		if self.coms['FT'] == False:
			temp2 = temp2.strip('\n')
			self.display.append(temp2)
		#formatting must be on, then use parameters to format
		elif segments:
			# reset newline parameters
			self.newcheck['lineone'] = False
			self.newcheck['needsecond'] = False
			for word in segments:
				#if empty, add margin
				if not self.temp:
					self.temp += " " * self.coms['LM']
				# if it fits, add the next word
				if len(self.temp) + len(word) < self.coms['LW']:
					# add spaces
					if self.coms['LM'] != len(self.temp):
						self.temp += " "
					self.temp += word
				#line is full, add to display and make empty
				else:
					for x in self.LS:
						self.temp = self.temp + "\n"
					self.display.extend([self.temp])
					self.temp = ""
					self.temp += " " * self.coms['LM']
					self.temp += word

		else:
			if self.newcheck['needsecond'] == True:
				self.display.append('')
			if self.temp:
				self.display.extend([self.temp])
				self.temp = ""
				self.display.extend([self.temp])
				self.newcheck['lineone'] = True
				self.newcheck['needsecond'] = True

	def get_lines(self):
		return self.display