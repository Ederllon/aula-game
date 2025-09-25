# raise SystemExit
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

        atk = int(input("Choose the country to ATACK (press 0 to exit): "))


        if atk == 0:
            print("\n EXIT ATACK PHASE!")
            loop_confirm = False
            return False

        if atk >= 1 and atk <= PlayersNumber:
            while True:
                df = int(input("Choose the country to DEFESE: "))
                if df > 0 and df <= PlayersNumber and df != atk and db_reg[df-1]["color"] != db_reg[atk-1]["color"]:
                    battle_result(atk, df)
                    return False
                print("CHOOSE INVALID, TRY AGAIN!\n") 
            return False
        print("CHOOSE INVALID, TRY AGAIN!\n") 

def battle_result(atackerPos, defenderPos):
    print("\n" + textTag_reg("BATTLE RESULT"))    
    diceAtk = randint(1,6)
    diceDef = randint(1,6)
    print("Country attacker {} roll {}".format(db_reg[atackerPos-1]["country"], diceAtk))
    print("Country defender {} roll {}".format(db_reg[defenderPos-1]["country"], diceDef))
    wl_action(atackerPos, defenderPos, diceAtk, diceDef)

def wl_action(compAtk, compDf, diceA, diceD):
    if diceA < diceD:
        print(db_reg[compDf-1]["color"] + " color won the atack from "+ db_reg[compAtk-1]["color"] + " over of " + db_reg[compDf-1]["country"] + " territory")
        db_reg[compAtk-1]["number"] = db_reg[compAtk-1]["number"]-1
    if diceD < diceA:
        print("The color " + db_reg[compAtk-1]["color"] + " dominated " + db_reg[compDf-1]["country"])
        db_reg[compDf-1]["color"] = db_reg[compAtk-1]["color"]
    if diceD == diceA:
        print("drawn!")

def winner_condition(max, db):
    return_condition = True
    c = max
    while c > 0:
        c = c - 1
        if (db[c-1]["color"]) == db[c]["color"]:  
            return_condition = True
        else:
            return_condition = False
            break
    if(return_condition == True):
        print(db[0]["color"] + " Ganhou!")
        raise SystemExit


#config-----------------------------------------------------------------------------
PlayersNumber = 2

db_reg = []

clear_db = False

#main-----------------------------------------------------------------------------
reg_init()

print(textTag_map())

loop_confirm = True

while loop_confirm:
    print("State: ")
    show_allPlayers()
    atack_phase()   
    winner_condition(PlayersNumber, db_reg) #maybe, change another place to write this
    ver = input("Press ENTER to continue... (press 0 to exit)") #0 not func
    
       
#post system-----------------------------------------------------------------------------
if clear_db == True:   
    db_reg = []


