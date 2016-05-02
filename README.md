# myfleet-fuji-equip
This project is to transfer equipment list from myfleet.moe to kancolle.wikia.com.<br />
You need to be registered in myfleet.moe if you want to use this program.<br /><br />
I have tested this project on Ubuntu 12.10 using Code::Blocks 13.12, this project is not tested on Windows.

#How To Use
Assume that you have been registered to myfleet.moe.
<ol>
<li>Copy the left table data content of equipment list from myfleet.moe (For example from : https://myfleet.moe/user/19019916/slotitem).
<li>Paste the data to /input/equip_data.txt then save the txt file (Overwrite). There's example data from the txt file.
<li>Copy the right table data content of equipment list from myfleet.moe (For example from : https://myfleet.moe/user/19019916/slotitem).
<li>Paste the data to /input/upgrade.txt then save the txt file (Overwrite). There's example data from the txt file.
<li>Run main.cpp with Code::Blocks IDE
<li>Go to /output/output.txt and copy all its content.
<li>Paste the content as wikia code. For Example : http://kancolle.wikia.com/wiki/User:Fujisuke/Equipment?action=edit
</ol>
