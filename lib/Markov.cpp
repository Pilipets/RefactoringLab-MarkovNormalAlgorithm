#include "Markov.hpp"


void RunAlgoritm(MarkovList ML, 
                    std::vector<command> Commands, 
                    bool show_all = false, 
                    bool simple_db = false, 
                    bool full_db = false)
{
    int cntr = 0, res;
 
    //debug data
    std::string prev;
    std::unordered_set <std::string> SET;

    while (true)    
    {
        if(cntr > MAX)
        {
            std::cout << "Here should be normal error mesage" << std::endl;
            goto end;
        }

        for(auto com:Commands)
        {
            ++cntr;

            if (show_all)
                std::cout << ML.data() << " --> ";
            //MAIN COMMAND
            res = ML.replace(com.first, com.second);


            // SIMPLE DEBUG
            if (simple_db)  
            {
                if (prev == ML.data())
                    {
                        std::cout << "Here should be normal error mesage" << std::endl;
                        goto end;
                    }
                else
                    prev = ML.data(); // fix it, not effective
            }
            // FULL DEBUG
            if (full_db)
            {
                if(SET.find(ML.data()) != SET.end())
                {
                        std::cout << "Here should be normal error mesage" << std::endl;
                        goto end;
                }
                SET.insert(ML.data());
            }
        
                    
            if (show_all)
                std::cout << ML.data() << std::endl;
                
            if(res && com.is_end)
                goto end;
            

            
        }
    }
    end:
    return;


}