while(!door_if.quit_doorcontrol_flag)
    {

        readHardware(confReader); //auslewhsen/updaten der sensorenliste

        //Automatikbetrieb
        if (confReader->betriebswahl()==0) //0 Automatikbetrieb
        {
        	confReader->lampe_an();
        	writeHardware(confReader);
        	sleep(5);
        	confReader->lampe_aus();
        	writeHardware(confReader);

        	while(confReader->betriebswahl()==0) {
        		readHardware(confReader);

        		if( !(confReader->endlage_offen()) &&
        		   (confReader->person_in_tuer() ||
        			confReader->manuelles_oeffnen() ||
					confReader->oeffnet()) )
        		{
        			confReader->oeffnen();
        		}

        		else if(confReader->endlage_offen())
        		{
        			confReader->motoren_stopp();
        			clock_t cpu_time = clock();
        			while( clock() < (cpu_time+3000) ) {
        				if(confReader->person_in_tuer() ||
        				   confReader->person_vor_tuer() ||
						   confReader->manuelles_oeffnen()) {
        					exit;
        				}
        			}
        			confReader->schliessen();
        		}

        		else if( (!(confReader->endlage_geschlossen()) ||
        				  !(confReader->person_in_tuer()) ||
						  !(confReader->person_vor_tuer())) &&
        				   confReader->schliesst())
        		{
        			confReader->schliessen();
        		}

        		else if(confReader->endlage_geschlossen()) {
        			confReader->motoren_stopp();
        		}
        	}

            writeHardware(confReader); //updaten der aktorenpins
        }


        while(confReader->betriebswahl()==1) //1 Handbetrieb
        {
        	readHardware(confReader);

        	if(!(confReader->endlage_offen())&&
        		(confReader->manuelles_oeffnen()||
        		 confReader->oeffnet()) )
        	{
        		confReader->oeffnen();
        	}

        	else if( ( !(confReader->endlage_geschlossen()) ||
        			   !(confReader->person_in_tuer()) ) &&
        			    (confReader->schliesst() ||
        			    confReader->manuelles_schliessen()) )
        	{
        		confReader->schliessen();
        	}

        	else if( confReader->endlage_geschlossen() ||
        			 confReader->endlage_offen() )
        	{
        		confReader->motoren_stopp();
        	}

            writeHardware(confReader); //updaten der aktorenpins
        }

        while(confReader->betriebswahl()==2) //2 Reparatur
        {
        	readHardware(confReader);

        	//achtung: mehrere_sensore_aktiv zu ein_sensor_aktiv geändert
        	if( confReader->ein_sensor_aktiv() &&
        		!(confReader->manuelles_schliessen()) )
        	{
        		confReader->oeffnen();
        		confReader->lampe_an();
        	}

        	else if( confReader->ein_sensor_aktiv() &&
        			 confReader->manuelles_schliessen() )
        	{
        		confReader->schliessen();
        		confReader->lampe_an();
        	}
        	// klären: sollen Endlagen in Reparatur aktiv sein?
        	else if( !(confReader->ein_sensor_aktiv()) ||
        			   confReader->endlage_offen() ||
					   confReader->endlage_geschlossen() )
        	{
        		confReader->motoren_stopp();
        		confReader->lampe_aus();
        	}

            writeHardware(confReader); //updaten der aktorenpins
        }
        // Falls Betriebsart gewechselt wird aber Lampe noch an ist.
        confReader->lampe_aus();
        writeHardware(confReader);

        while(confReader->betriebswahl()==3) //3 Aus
        {
            confReader->motoren_stopp();
            writeHardware(confReader); //updaten der aktoren
        }

        //construct counter message
        msg = "press 'q'";

        // set current message to be displayed by user interface
        door_if.DebugString(msg);
    }
}
