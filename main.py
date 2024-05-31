#!/usr/bin/python

# Copyright (C) Anasov <me@anasov.ly> - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Anasov <me@anasov.ly>, 05, May, 2024.

from email.policy import default
import random
from time import sleep
import json, os, signal, sys
from tracemalloc import start
from rich.console import Console
from rich.prompt import Prompt, IntPrompt
from cpmnuker import CPMNuker


__CHANNEL_USERNAME__    = "CPMNuker"
__GROUP_USERNAME__      = "CPMNukerChat"

def signal_handler(sig, frame):
    print("\n Bye Bye...")
    sys.exit(0)

def banner(console):
    os.system('cls' if os.name == 'nt' else 'clear')
    console.print("[bold green]♕ CPMNuker[/bold green]: Car Parking Multiplayer Hacking ToolKit.")
    console.print(f"[bold green]♕ Telegram[/bold green]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue] or [bold blue]@{__GROUP_USERNAME__}[/bold blue].")
    console.print("=====================================================")
    console.print("[bold yellow]! Note[/bold yellow]: Logout from the account before using this tool !.", end="\n\n")

def load_player_data(cpm):
    data = cpm.get_player_data().get('data')
    console.print("[bold][red]========[/red][ PLAYER DETAILS ][red]========[/red][/bold]")
    console.print(f"[bold green] Name   [/bold green]: { (data.get('Name') if 'Name' in data else 'UNDEFINED') }.")
    console.print(f"[bold green] LocalID[/bold green]: { (data.get('localID')  if 'localID' in data else 'UNDEFINED') }.")
    console.print(f"[bold green] Money  [/bold green]: { (data.get('money')  if 'money' in data else 'UNDEFINED') }.")
    console.print(f"[bold green] Coins  [/bold green]: { (data.get('coin')  if 'coin' in data else 'UNDEFINED') }.", end="\n\n")

def load_key_data(cpm):
    data = cpm.get_key_data()
    console.print("========[ ACCESS KEY DETAILS ]========")
    console.print(f"[bold green] Access Key [/bold green]: { data.get('access_key') }.")
    console.print(f"[bold green] Telegram ID[/bold green]: { data.get('telegram_id') }.")
    console.print(f"[bold green] Credits    [/bold green]: { data.get('coins') }.", end="\n\n")

def interpolate_color(start_color, end_color, fraction):
    start_rgb = tuple(int(start_color[i:i+2], 16) for i in (1, 3, 5))
    end_rgb = tuple(int(end_color[i:i+2], 16) for i in (1, 3, 5))
    interpolated_rgb = tuple(int(start + fraction * (end - start)) for start, end in zip(start_rgb, end_rgb))
    return "{:02x}{:02x}{:02x}".format(*interpolated_rgb)

def rainbow_gradient_string(customer_name):
    modified_string = ""
    num_chars = len(customer_name)
    start_color = "{:06x}".format(random.randint(0, 0xFFFFFF))
    end_color = "{:06x}".format(random.randint(0, 0xFFFFFF))
    for i, char in enumerate(customer_name):
        fraction = i / max(num_chars - 1, 1)
        interpolated_color = interpolate_color(start_color, end_color, fraction)
        modified_string += f'[{interpolated_color}]{char}'
    return modified_string

if __name__ == "__main__":
    console = Console()
    signal.signal(signal.SIGINT, signal_handler)
    while True:
        banner(console)
        acc_email = Prompt.ask("[bold]➤ Account Email[/bold]", password=False)
        acc_password = Prompt.ask("[bold]➤ Account Password[/bold]", password=True)
        acc_access_key = Prompt.ask("[bold]➤ Access Key[/bold]", password=False)
        if acc_email == "" or acc_password == "" or acc_access_key == "": continue
        console.print("[bold cyan]↻ Trying to Login[/bold cyan]: ", end=None)
        cpm = CPMNuker(acc_access_key)
        login_response = cpm.login(acc_email, acc_password)
        match login_response:
            case 0:
                print("SUCCESSFUL.")
                sleep(1)
            case 100:
                print("EMAIL NOT FOUND.")
                sleep(1)
                continue
            case 101:
                print("INVALID PASSWORD.")
                sleep(1)
                continue
            case 103:
                print("INVALID ACCESS KEY.")
                sleep(1)
                continue
            case 106:
                print("MISSING PASSWORD.")
                sleep(1)
                continue
            case 107:
                print("INVALID EMAIL.")
                sleep(1)
                continue
            case 108:
                print("MISSING EMAIL.")
                sleep(1)
                continue
            case 109:
                print("ACCESS KEY BLOCKED.")
                sleep(1)
                continue
            case _:
                print("UNKNOWN ERROR.")
                sleep(1)
                continue
        while True:
            banner(console)
            load_player_data(cpm)
            load_key_data(cpm)
            console.print("[bold cyan](1): Increase Money[/bold cyan]")
            console.print("[bold cyan](2): Increase Coins[/bold cyan]")
            console.print("[bold cyan](3): King Rank[/bold cyan]")
            console.print("[bold cyan](4): Change ID[/bold cyan]")
            console.print("[bold cyan](5): Change Name[/bold cyan]")
            console.print("[bold cyan](6): Change Name (Rainbow)[/bold cyan]")
            console.print("[bold cyan](7): Unlock All Cars[/bold cyan]")
            console.print("[bold cyan](8): Account Delete[/bold cyan]")
            console.print("[bold cyan](9): Account Register[/bold cyan]")
            console.print("[bold cyan](0): Exit[/bold cyan]", end="\n\n")
            service = IntPrompt.ask("[bold]➤ Select a Service[/bold]", choices=["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"])
            match service:
                case 0: # Exit
                    console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                    break
                case 1: # Increase Money
                    console.print("[bold cyan]✶ Insert how much money do you want.[/bold cyan]")
                    amount = Prompt.ask("[bold]➤ Amount[/bold]")
                    console.print("[bold cyan]↺ Saving your data[/bold cyan]: ", end=None)
                    if cpm.set_player_data({"money": amount}):
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        answ = Prompt.ask("[bold cyan]➤ Do You want to Exit ?[/bold cyan]", choices=["y", "n"])
                        if answ == "y": console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                        else: continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
                case 2: # Increase Coins
                    console.print("[bold cyan]✶ Insert how much coins do you want.[/bold cyan]")
                    amount = Prompt.ask("[bold]➤ Amount[/bold]")
                    console.print("[bold cyan]↺ Saving your data[/bold cyan]: ", end=None)
                    if cpm.set_player_data({"coin": amount}):
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        answ = Prompt.ask("[bold cyan]➤ Do You want to Exit ?[/bold cyan]", choices=["y", "n"])
                        if answ == "y": console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                        else: continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
                case 3: # King Rank
                    console.print("[bold cyan]↺ Giving you a King Rank[/bold cyan]: ", end=None)
                    if cpm.set_player_rank():
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        answ = Prompt.ask("[bold cyan]➤ Do You want to Exit ?[/bold cyan]", choices=["y", "n"])
                        if answ == "y": console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                        else: continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
                case 4: # Change ID
                    console.print("[bold cyan]✶ Enter your new ID.[/bold cyan]")
                    new_id = Prompt.ask("[bold]➤ ID[/bold]")
                    console.print("[bold cyan]↺ Saving your data[/bold cyan]: ", end=None)
                    if cpm.set_player_data({"localID": new_id}):
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        answ = Prompt.ask("[bold cyan]➤ Do You want to Exit ?[/bold cyan]", choices=["y", "n"])
                        if answ == "y": console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                        else: continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
                case 5: # Change Name
                    console.print("[bold cyan]✶ Enter your new Name.[/bold cyan]")
                    new_name = Prompt.ask("[bold]➤ Name[/bold]")
                    console.print("[bold cyan]↺ Saving your data[/bold cyan]: ", end=None)
                    if cpm.set_player_data({"name": new_name}):
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        answ = Prompt.ask("[bold cyan]➤ Do You want to Exit ?[/bold cyan]", choices=["y", "n"])
                        if answ == "y": console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                        else: continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
                case 6: # Change Name Rainbow
                    console.print("[bold cyan]✶ Enter your new Rainbow Name.[/bold cyan]")
                    new_name = Prompt.ask("[bold]➤ Name[/bold]")
                    console.print("[bold cyan]↺ Saving your data[/bold cyan]: ", end=None)
                    if cpm.set_player_data({"name": rainbow_gradient_string(new_name)}):
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        answ = Prompt.ask("[bold cyan]➤ Do You want to Exit ?[/bold cyan]", choices=["y", "n"])
                        if answ == "y": console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                        else: continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
                case 7: # Unlock All Cars
                    continue
                case 8: # Account Delete
                    console.print("[bold cyan]✶ After deleting your account there is no going back !!.[/bold cyan]")
                    answ = Prompt.ask("[bold cyan]➤ Do You want to Delete this Account ?![/bold cyan]", choices=["y", "n"])
                    if answ == "y":
                        cpm.delete()
                        console.print("[bold cyan]↺ Deleting Your Account[/bold cyan]: [bold green]SUCCESSFUL.[/bold green].")
                        console.print("==================================")
                        console.print(f"[bold yellow]✴ Thank You for using our tool, please join our telegram channel[/bold yellow]: [bold blue]@{__CHANNEL_USERNAME__}[/bold blue].")
                    else: continue
                case 9: # Account Register
                    console.print("[bold cyan]✶ Registring new Account.[/bold cyan]")
                    acc2_email = Prompt.ask("[bold]➤ Account Email[/bold]", password=False)
                    acc2_password = Prompt.ask("[bold]➤ Account Password[/bold]", password=True)
                    console.print("[bold cyan]↺ Creating new Account[/bold cyan]: ", end=None)
                    status = cpm.register(acc2_email, acc2_password)
                    if status == 0:
                        console.print("[bold green]SUCCESSFUL.[/bold green]")
                        console.print("==================================")
                        console.print(f"[bold yellow]! You've been automatically signed in as[/bold yellow]: [blue]{acc2_email}[/blue]")
                        sleep(2)
                        continue
                    elif status == 105:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ This email is already exists !.[/bold yellow]")
                        sleep(2)
                        continue
                    else:
                        console.print("[bold red]FAILED.[/bold red]")
                        console.print("[bold yellow]✶ Please try again.[/bold yellow]")
                        sleep(2)
                        continue
            break
        break
    