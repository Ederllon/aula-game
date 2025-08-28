#func text format-------------------------------------------------------------
def textTag_reg(text):
    textTag = "--- {} ---".format(text)
    return textTag

def textTag_map(): 
    textTag = '\n'+30*"="+"\n WORLD MAP - CURRENT SITUATION \n"+30*"="
    return textTag

def textTag_country(text):
    textTag = "- {}".format(text)
    return textTag

#func in exec-----------------------------------------------------------------------------
def reg_init():
    print("\n register {} country for game world: \n \n".format(PlayersNumber).upper()+'-'*40)
    for count in range(PlayersNumber): 
        print('\n' + textTag_reg("Register the {} country".format(count+1)))
        new_reg_country = input("Country name: ").lower()
        new_reg_trooperColor = input("Trooper color:  ").lower()
        new_reg_numberTrooper = int(input("Trooper number: "))
        db_reg.append ({'country' : new_reg_country, 'color' : new_reg_trooperColor, 'number' : new_reg_numberTrooper})

def show_allPlayers():
    for count in range(PlayersNumber):
        print("\n COUNTRY {}:".format(count+1))
        print(textTag_country("Name: " + str(db_reg[count]['country'])))
        print(textTag_country("Dominated color: {} trooper" .format(str(db_reg[count]['color']))))
        print(textTag_country("Troopers: " + str(db_reg[count]['number'])))

#config-----------------------------------------------------------------------------
PlayersNumber = 5
db_reg = []

#main-----------------------------------------------------------------------------
reg_init()

print(textTag_map())

show_allPlayers()





#text-----------------------------------------------------------------------------


