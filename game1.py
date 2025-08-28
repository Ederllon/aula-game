#import----------------------------------------------------------------------
from random import randint

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

def atack_phase():
    print("\n" + textTag_reg("ATACK PHASE"))
    while True:
        atk = int(input("Choose the country to ATACK: "))
        if atk >= 1 and atk <= PlayersNumber:
            while True:
                df = int(input("Choose the country to DEFESE: "))
                if df > 0 and df <= PlayersNumber and df != atk:
                    return False
                print("CHOOSE INVALID, TRY AGAIN!\n") 

            return False
        print("CHOOSE INVALID, TRY AGAIN!\n") 
    
    print("\n" + textTag_reg("BATTLE RESULT"))

#config-----------------------------------------------------------------------------
PlayersNumber = 2

db_reg = []

clear_db = False

#main-----------------------------------------------------------------------------
reg_init()

print(textTag_map())

show_allPlayers()

atack_phase()   



if clear_db == True:
    db_reg = []
#text-----------------------------------------------------------------------------

