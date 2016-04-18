#include <fstream>
#include <iostream>
#include <stdio.h>

//For Linux
#define SIMPLE_UPGRADE_PATH "process/simple_upgrade.txt"
#define SIMPLE_OUTPUT_PATH "process/simple_output.txt"
#define EQUIP_DATA_PATH "input/equip_data.txt"
#define TYPE_PATH "input/type.txt"
#define TYPE_SEPARATOR_PATH "input/type_separator.txt"
#define OUTPUT_PATH "output/output.txt"
#define UPGRADE_PATH "input/upgrade.txt"

#include "split.h";

struct
{
    string type="";
    string name="";
    string upgrade="";
    string ja="";
    string amount="";
}equip;

void simplerUpgrade();
void process_simple_output();
void process_output();
void view_output();

int main()
{
    simplerUpgrade();
    process_simple_output();
    process_output();
    view_output();
    return 0;
}

void simplerUpgrade()
{
    FILE *simple_upgrade = fopen(SIMPLE_UPGRADE_PATH, "wt");
    string str;
    string tempUpgrade = "";
    ifstream file(UPGRADE_PATH);
    int counter = 1;
    while (getline(file, str))
    {
        if(tempUpgrade.compare(str)==0)
        {
            counter++;
            continue;
        }
        else
        {
            if(tempUpgrade.compare("")>0)
            {
                fprintf(simple_upgrade, "%s+%d\n", tempUpgrade.c_str(), counter);
            }
            tempUpgrade = str;
            counter = 1;
        }
    }
    fprintf(simple_upgrade, "%s+%d\n", tempUpgrade.c_str(), counter);
    file.close();
    fclose(simple_upgrade);
}
void process_simple_output()
{
    FILE *output = fopen(SIMPLE_OUTPUT_PATH, "wt");
    ifstream file(EQUIP_DATA_PATH);
    string str, s_type;
    vector<string> x,y;
    while (getline(file, str))
    {
        equip.ja="";
        //{{FujiTitle | title= Guns}}
        //{{FujiEquip | type= smallgun |name= 12.7cm Twin Gun Mount Model B Kai 2| upgrade= |ja= 12.7cm連装砲B型改二 |amount= 2}}
        x = split(str, ' ');
        for (int i=0; i < x.size(); i++)
        {
            if(i == x.size()-1)
            {
                equip.amount=x[i];
            }
            else
            {
                equip.ja.append(x[i]);
                if(i < x.size()-2)
                {
                    equip.ja.append(" ");
                }
            }
        }
        ifstream type(TYPE_PATH);
        int stats = 0; // 0=not found, 1=found
        while (getline(type, s_type))
        {
            y = split(s_type, '|');
            if(y[2].compare(equip.ja)==0)
            {
                equip.type = y[0];
                equip.name = y[1];
                stats = 1;
                break;
            }
        }
        if(stats==0)
        {
            equip.type = "";
            equip.name = "";
            equip.amount = "";
        }
        type.close();
        ifstream upgrade(SIMPLE_UPGRADE_PATH);
        equip.upgrade = "";
        while (getline(upgrade, s_type))
        {//find
            y = split(s_type, '+');
            if(y[0].compare(equip.ja)==0)
            {
                equip.upgrade.append("★+");
                equip.upgrade.append(y[1]);
                equip.upgrade.append(" x");
                equip.upgrade.append(y[2]);
                equip.upgrade.append("<br />");
            }
        }
        upgrade.close();

        fprintf(output, "{{FujiEquip | type= %s |name= %s| upgrade= %s |ja= %s |amount= %s}}\n", equip.type.c_str(), equip.name.c_str(), equip.upgrade.c_str(), equip.ja.c_str(), equip.amount.c_str());
    }
    fclose(output);
    file.close();
}

void process_output()
{
    FILE *t_separator = fopen(TYPE_SEPARATOR_PATH, "rt");
    FILE *output = fopen(OUTPUT_PATH, "wt");
    FILE *s_output;

    string name, type, current_name, s_type;
    char tmp[2][200];
    vector<string> x,y;
    current_name = "";
    fscanf(t_separator, "%s %s", tmp[0], tmp[1]);
    name=tmp[0]; type=tmp[1];
    fprintf(output, "{{FujiEquipList\n|list=\n");
    while(!feof(t_separator))
    {
        if(name.compare(current_name)!=0)
        {
            fprintf(output, "{{FujiTitle | title= %s}}\n", name.c_str());
            current_name = name;
        }
        ifstream s_output(SIMPLE_OUTPUT_PATH);
        while (getline(s_output, s_type))
        {
            x = split(s_type, '|');
            y = split(x[1], ' ');
            if(y[2].compare(type)==0)
            {
                fprintf(output, "%s\n", s_type.c_str());
            }
        }
        s_output.close();
        fscanf(t_separator, "%s %s", tmp[0], tmp[1]);
        name=tmp[0]; type=tmp[1];
    }
    fprintf(output, "}}\n\n___NOTOC___");
    fclose(output);
    fclose(t_separator);
}

void view_output()
{
    ifstream output(OUTPUT_PATH);
    string out;
    while (getline(output, out))
    {
        cout << out << "\n";
    }

}
