#include "Cache.h"

namespace G
{
    typedef bitset<32> bits;
    
   
    Cache::Cache(int& C, int&b, int&N)
    {
        capacity     = C;
        block_size    = B;
        assoc        = N;
        
        createCache();
        
        cout << "Capacity: " << C << endl;
        cout << "Block Size: " << B << endl;
        cout << "Associativity: " << N << endl;
        cout << "Total blocks: " << blocks << endl;
        cout << "Total sets: " << sets << endl;
        cout << "Offset bits: " << offset << endl;
        cout << "Index bits: " << index << endl;
        cout << "Tag bits: " << tag << endl;
    }
    
    Cache::~Cache() {
        free(bank);    //Free memory allocated for the array of structs
    }
    
    
    void Cache::testMem()
    {
       
        bank = (mem_address*)malloc(sizeof(mem_address)*memoryLength);

        
        for(int i=0; i<memoryLength; i++)
        {
            bank[i].mem     = memory.at(i);
            bank[i].tag     = getTag(memory.at(i));
            bank[i].index     = getIndex(memory.at(i));
            bank[i].offset     = getOffset(memory.at(i));

        }
        
        
        int i=0;
        for(; i<memoryLength; i++)
        {
//           
            checkEntry(bank[i]);
//            
        }
        
        cout << "NUM ACCESSES " << i << endl;
        cout << "HITS: " << hits << endl;
        cout << "MISSES: " << misses << endl;
        cout << "HIT RATE: " << (double)(hits)/(double)(i) << endl;
        
        
    }
   
    void Cache::printMemAdr(mem_address& adr)
    {
        cout << "MEM:\t" << adr.mem <<
                "\nTAG:\t" << adr.tag <<
                "\nINDEX:\t" << adr.index <<
                "\nOFFSET:\t" << adr.offset << endl;
    }
    
    
    void Cache::checkEntry(mem_address& adr)
    {
        int currentIndex                     = bitsToInt(adr.index);            

        list<tagentry>* currentSet             = &tagCache.at(currentIndex);     
        
        list<tagentry>::iterator* currentIt = &tagIt.at(currentIndex);        
            
        *currentIt = find(currentSet->begin(), currentSet->end(), adr.tag);   
        
      
        if(currentSet->size() == assoc)
        {
           
            if( (*currentIt == currentSet->end()) )
            {
                misses++;
                
                *currentIt = currentSet->begin();    
                currentSet->erase(*currentIt);        
                currentSet->push_back(adr.tag);        
                
               
                *currentIt = currentSet->begin();
                advance(*currentIt, distance(*currentIt, currentSet->end())-1); 

            }
            
            
            else
            {
                hits++;
                
                currentSet->erase(*currentIt);
                
                currentSet->push_back(adr.tag);
                
              
                *currentIt = currentSet->begin();
                advance(*currentIt, distance(*currentIt, currentSet->end())-1); 
                
            }
        }
        
        else if ( (currentSet->size() != 0) && (currentSet->size() < assoc))
        {
            /*Cache MISS, Compulsory Miss*/
            if( (*currentIt == currentSet->end()) )
            {
                misses++;
                
                currentSet->push_back(adr.tag);
                
                
                *currentIt = currentSet->begin();
                advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement
                
            }
           
            else
            {
                hits++;
                
                currentSet->erase(*currentIt);    

                currentSet->push_back(adr.tag);
                
            }
        }
       
        else if( (currentSet->size() == 0) && (*currentIt == currentSet->end()) )
        {
            misses++;
            
            currentSet->push_back(adr.tag);       
            *currentIt = currentSet->begin();   
        }
        
       
        if( (**currentIt) != adr.tag)
        {
            cout << "ERROR @ " << currentIndex << " mem:" << endl;
            printMemAdr(adr);
            printSet(*currentSet);
            exit(0);
        }
        
       
        currentSet = nullptr;
        currentIt = nullptr;
        delete currentSet;
        delete currentIt;
    }
    
    
    void Cache::printSet(list<tagentry>& l)
    {
        int i=0;
        for(list<tagentry>::iterator j= l.begin(); j != l.end(); j++)
        {
            cout << "Index: " << i << " " << *j << endl;
            i++;
        }
    }
    
    
    void Cache::deleteMemEntry(mem_address*& adr)
    {
        cout << "Deleting ptr: " << adr << endl;
        adr = nullptr;
        delete adr;
    }
    
    /*Initialize values for the cache*/
    void Cache::createCache()
    {
        blocks     = capacity/block_size;
        sets    = blocks/assoc;
        offset     = log(block_size)/log(2);
        index     = log(sets)/log(2);
        tag     = 32 - offset - index;
        
        hits    = 0;
        misses    = 0;
        
        
        tagCache.resize(sets);
        tagIt.resize(sets);
        
       
        for(int i=0; i<sets; i++)
        {
            tagIt.at(i) = tagCache.at(i).begin();
        }
    }
    
  
    void Cache::readMemory() {
        ifstream file;
        string line;
        string file_name;

        cout<<"Enter name of file with memory addresses: ";
        cin>>file_name;

    file.open("example.trc", ios::in);
        file.open(file_name, ios::in);
        
        int j=0;
        
       
        while(!file.eof())
        {
            getline(file,line);

           
            if(line.length()<2)
            {
                break;
            }
            
          
            memory.push_back(hexToBin(line));
            
            j++;
        }

        cout << "Read in " << j << " memory addresses from the file" << endl;
        
        memoryLength = j; 
        file.close();
    }
    
    
    bits Cache::hexToBin(string& s)
    {
        stringstream ss;
        unsigned int n;
        
       
        ss << hex << s;
        ss >> n;
        
       
        bitset<32> b(n);

        return b;
    }
    
    
    bits Cache::getTag(bits& h)
    {
        bitset<32> b(h.to_string(), 0, tag);
        
        return b;
    }
    
    
    bits Cache::getIndex(bits& h)
    {
        bitset<32> b(h.to_string(), tag, index);
        
        return b;
    }
    
   
    bits Cache::getOffset(bits& h)
    {
        bitset<32> b(h.to_string(), index+tag, 31);
        
        return b;
    }
    
    
    int Cache::bitsToInt(bits& h)
    {
        int b = stoi(h.to_string(), nullptr, 2);
      
        
        return b;
    }

}
