#include <bits/stdc++.h>
using namespace std;

// Global PID
int pid = 1;


unordered_map<int, string> procNamewithPID;
unordered_map<int, int> pageaccesstime;

void updateacesstime(vector<int>&mainmemory, int page)
{
  pageaccesstime[page] = pid++;
}

//lru 
int lru(vector<int>&mainmemory)
{
  int min = INT_MAX;
  int minpage = -1;
  for(int i = 0; i < mainmemory.size(); i++)
  {
    if(mainmemory[i] != -1 && pageaccesstime[mainmemory[i]] < min)
    {
      min = pageaccesstime[mainmemory[i]];
      minpage = i;
    }
  }
  return minpage;
}

// Function to execute the "add" command
void executeAdd(vector<int> &mainmemory, int x, int y, int z) {
  // Check if x, y, and z are valid memory addresses
  if (x < 0 || x >= mainmemory.size() || y < 0 || y >= mainmemory.size() || z < 0 || z >= mainmemory.size()) {
    cout << "Invalid Memory Address specified" << endl;
    return;
  }

  // Perform the addition and store the result in memory address z
  mainmemory[z] = mainmemory[x] + mainmemory[y];

  // Output the command and result
  cout << "Command: add " << x << ", " << y << ", " << z << "; Result: Value in addr " << x
       << " = " << mainmemory[x] << ", addr " << y << " = " << mainmemory[y] << ", addr " << z
       << " = " << mainmemory[z] << endl;
}

// Function to execute the "sub" command
void executeSubtract(vector<int> &mainmemory, int x, int y, int z) {
  // Check if x, y, and z are valid memory addresses
  if (x < 0 || x >= mainmemory.size() || y < 0 || y >= mainmemory.size() || z < 0 || z >= mainmemory.size()) {
    cout << "Invalid Memory Address specified" << endl;
    return;
  }

  // Perform the subtraction and store the result in memory address z
  mainmemory[z] = mainmemory[x] - mainmemory[y];

  // Output the command and result
  cout << "Command: sub " << x << ", " << y << ", " << z << "; Result: Value in addr " << x
       << " = " << mainmemory[x] << ", addr " << y << " = " << mainmemory[y] << ", addr " << z
       << " = " << mainmemory[z] << endl;
}

// Function to execute the "print" command
void executePrint(vector<int> &mainmemory, int x) {
  // Check if x is a valid memory address
  if (x < 0 || x >= mainmemory.size()) {
    cout << "Invalid Memory Address specified" << endl;
    return;
  }

  // Output the command and value at memory address x
  cout << "Command: print " << x << "; Result: Value in addr " << x << " = " << mainmemory[x] << endl;
}

// Function to execute the "load" command
void executeLoad(vector<int> &mainmemory, int a, int y) {
  // Check if y is a valid memory address
  if (y < 0 || y >= mainmemory.size()) {
    cout << "Invalid Memory Address specified" << endl;
    return;
  }

  // Store the value of a in memory address y
  mainmemory[y] = a;

  // Output the command and result
  cout << "Command: load " << a << ", " << y << "; Result: Value of " << a << " is now stored in addr " << y << endl;
}


void runexecmd(vector<int> &mainmemory, vector<int> &virtualMemory, int pid) {
  if (pid < 1 || pid > virtualMemory.size()) {
    cout << "Error: Invalid PID" << endl;
    return;
  }
  // if (virtualMemory.size() > mainmemory.size()) {
  //   cout << "Error: Not enough space in main memory for process " << pid
  //        << endl;
  //   return;
  // }
bool flag = false;
  // Check if the process is in virtual memory and has not been killed
  for (int i = 0; i < virtualMemory.size(); i++) {
    if (virtualMemory[i] == pid) {
      // Find an empty page in main memory
      for (int j = 0; j < mainmemory.size(); j++) {
        if (mainmemory[j] == -1) {
          mainmemory[j] = pid;
          cout << "Process " << pid << " has been loaded into main memory"
               << endl;
          return;
        }
      }

      // If no empty page is found, swap out a page using LRU
      int pageToSwap = lru(mainmemory);
      mainmemory[pageToSwap] = pid;
      cout << "Process " << pid << " has been loaded into main memory"
           << endl;
      flag = true;
    }
  }

  // Check if the process is already in main memory and has not been killed
  if(flag!=true)
  for (int i = 0; i < mainmemory.size(); i++) {
    if (mainmemory[i] == pid) {
      flag = true;
      // cout << "Process " << pid << " is already in main memory" << endl;
    }
  }


  if(flag==false){
    cout << "Process " << pid << " has not been loaded" << endl;
    return;
  }


//open file corresponding to the pid
  string filename = procNamewithPID[pid];

  ifstream file(filename);
  if (!file) {
    cout << "Error: Could not open file " << filename << endl;
    return;
  } 

  string command;
  while (getline(file, command)) {
    stringstream ss(command);
    string cmd;
    ss >> cmd;
    if (cmd == "add") {
      int x, y, z;
      ss >> x >> y >> z;
      executeAdd(mainmemory, x, y, z);
    } else if (cmd == "sub") {
      int x, y, z;
      ss >> x >> y >> z;
      executeSubtract(mainmemory, x, y, z);
    } else if (cmd == "print") {
      int x;
      ss >> x;
      executePrint(mainmemory, x);
    } else if (cmd == "load") {
      int a, y;
      ss >> a >> y;
      executeLoad(mainmemory, a, y);
    }
  }

 
  file.close(); 

  


}


void kill(vector<int> &mainmemory, vector<int> &virtualMemory, int pid) {
  if (pid < 1 || pid > virtualMemory.size()) {
    cout << "Error: Invalid PID" << endl;
    return;
  }

  // Remove the process from main memory
  for (int i = 0; i < mainmemory.size(); i++) {
    if (mainmemory[i] == pid) {
      mainmemory[i] = -1;
    }
  }

  // Remove the process from virtual memory
  for (int i = 0; i < virtualMemory.size(); i++) {
    if (virtualMemory[i] == pid) {
      virtualMemory[i] = -1;
    }
  }

  cout << "Process " << pid << " has been killed and its memory has been freed"
       << endl;

       
}

void load(vector<int> &mainmemory, vector<int> &virtualMemory, int P,
          string filename) {
  ifstream file(filename);
  if (!file) {
    cout << "Error: Could not open file " << filename << endl;
    return;
  }
  int processSize = 0;
  file >> processSize;
  file.close();

  int processSizeinBytes = processSize * 1024;
  int processSizeinPages = processSizeinBytes / P;

  int idx = 0, cnt = 0;
  bool nomm = false;
  if (processSizeinPages > mainmemory.size()) {
    cout << "Error: Not enough space in main memory for process " << filename
         << endl;
    nomm = true;
  }

  if (processSizeinPages > virtualMemory.size()) {
    cout << "Error: Not enough space in virtual memory for process " << filename
         << endl;
    return;
  } else if (nomm) {
    goto label1;
  }

  for (auto ii : mainmemory) {
    if (ii == -1) {
      mainmemory[idx] = pid;
      cnt++;
      if (cnt == processSizeinPages) {
        break;
      }
    }
    idx++;
  }

  if (cnt == processSizeinPages) {
    cout << "Process " << filename << " loaded into main memory" << endl;
    procNamewithPID[pid] = filename;
    pid++;
    return;


    //print the contents of the file 
  //  cout<<"Contents of the file are"<<endl;
  //   ifstream file(filename);
  //   string line;
    

  }

label1:
  idx = 0;
  cnt = 0;
  for (auto ii : virtualMemory) {
    if (ii == -1) {
      virtualMemory[idx] = pid;
      cnt++;
      if (cnt == processSizeinPages) {
        break;
      }
    }
    idx++;
  }
  cout << "Process " << filename << " loaded into virtual memory" << endl;
  pid++;
}

// Function to print the page table entry information for a process
void pte(const vector<int> &mainmemory, int pid, const string &filename) {
  if (pid < 0 || pid >= mainmemory.size()) {
    cout << "Error: Invalid PID specified." << endl;
    return;
  }

  ofstream output(filename, ios::app); // Open the output file in append mode

  if (!output) {
    cout << "Error: Could not open file " << filename << endl;
    return;
  }

  output << "Page Table Entry Information for PID " << pid << ":\n";

  for (int i = 0; i < mainmemory.size(); i++) {
    if (mainmemory[i] == pid) {
      output << "Logical Page: " << i << ", Physical Page: " << i << "\n";
    }
  }

  output.close();
  cout << "Page table entry information for PID " << pid << " written to "
       << filename << endl;
}

// //listpr
// Print to screen the identifier values of all processes in main memory and in
// virtual memory: print the pids of processes in main memory first (sorted by
// pid), followed by pids of processes in virtual memory (sorted by pid).

void listpr(vector<int> &mainmemory, vector<int> &virtualMemory) {
  vector<int> pids;
  for (int i = 0; i < mainmemory.size(); i++) {
    if (mainmemory[i] != -1 &&
        find(pids.begin(), pids.end(), mainmemory[i]) == pids.end()) {
      pids.push_back(mainmemory[i]);
    }
  }
  for (int i = 0; i < virtualMemory.size(); i++) {
    if (virtualMemory[i] != -1 &&
        find(pids.begin(), pids.end(), virtualMemory[i]) == pids.end()) {
      pids.push_back(virtualMemory[i]);
    }
  }
  sort(pids.begin(), pids.end());
  cout << "PIDs of processes in main memory: ";
  for (int i = 0; i < pids.size(); i++) {
    if (find(mainmemory.begin(), mainmemory.end(), pids[i]) !=
        mainmemory.end()) {
      cout << pids[i] << " ";
    }
  }
  cout << endl;
  cout << "PIDs of processes in virtual memory: ";
  for (int i = 0; i < pids.size(); i++) {
    if (find(virtualMemory.begin(), virtualMemory.end(), pids[i]) !=
        virtualMemory.end()) {
      cout << pids[i] << " ";
    }
  }
  cout << endl;
}
// Function to print all page table entries in ascending PID order
void pteall(const vector<int> &mainmemory, const vector<int> &virtualMemory,
            const string &filename) {
  ofstream output(filename, ios::app); // Open the output file in append mode

  if (!output) {
    cout << "Error: Could not open file " << filename << endl;
    return;
  }

  // Get unique PIDs in ascending order from both main memory and virtual memory
  set<int> uniquePIDs;
  for (int pid : mainmemory) {
    if (pid != -1) {
      uniquePIDs.insert(pid);
    }
  }
  for (int pid : virtualMemory) {
    if (pid != -1) {
      uniquePIDs.insert(pid);
    }
  }

  output << "Page Table Entry Information (All PIDs in Ascending Order):\n";

  // Iterate through unique PIDs and print their page table entries
  for (int pid : uniquePIDs) {
    output << "Page Table Entry Information for PID " << pid << ":\n";
    for (int i = 0; i < mainmemory.size(); i++) {
      if (mainmemory[i] == pid) {
        output << "Logical Page (Main Memory): " << i
               << ", Physical Page: " << i << "\n";
      }
    }
    for (int i = 0; i < virtualMemory.size(); i++) {
      if (virtualMemory[i] == pid) {
        output << "Logical Page (Virtual Memory): " << i
               << ", Physical Page: " << i << "\n";
      }
    }
  }
  output.close();
  cout << "Page table entry information for all PIDs written to " << filename
       << endl;
}

// Function to swap out a process specified by pid into virtual memory
void swapout(vector<int> &mainmemory, vector<int> &virtualMemory, int pid) {
  if (pid < 0 || pid >= virtualMemory.size()) {
    cout << "Error: Invalid PID specified." << endl;
    return;
  }

  int mainMemoryPages = mainmemory.size();

  // Iterate through main memory to find and swap out pages associated with the
  // specified pid
  for (int i = 0; i < mainMemoryPages; i++) {
    if (mainmemory[i] == pid) {
      // Update virtual memory to indicate that this page is now in virtual
      // memory
      virtualMemory[i] = pid;

      // Clear the page in main memory
      mainmemory[i] = -1;
    }
  }

  cout << "Process with PID " << pid << " swapped out into virtual memory."
       << endl;
}

void printMemory(const vector<int> &mainmemory, int memloc, int length) {
  for (int i = 0; i < length; i++) {
    int address = memloc + i;

    // Check if the address is within the bounds of main memory
    if (address >= 0 && address < mainmemory.size()) {
      int value = mainmemory[address];
      cout << "Value of " << address << ": " << value << endl;
    } else {
      cout << "Value of " << address << ": 0" << endl;
    }
  }
}




void executeSwapIn(vector<int> &mainmemory, vector<int> &virtualMemory, int pid) {
  // Check if pid is valid
  if (pid < 1 || pid > virtualMemory.size()) {
    cout << "Error: Invalid PID" << endl;
    return;
  }

  // Check if the process is already in main memory
  for (int i = 0; i < mainmemory.size(); i++) {
    if (mainmemory[i] == pid) {
      cout << "Process " << pid << " is already in main memory" << endl;
      return;
    }
  }

  // Check if there is enough capacity in main memory
  int mainMemoryCapacity = mainmemory.size();
  int currentProcessCount = count(mainmemory.begin(), mainmemory.end(), -1);
  if (currentProcessCount < 1) {
    // No room in main memory, swap out the last run process using LRU
    int pageToSwap = lru(mainmemory);
    int processToSwap = mainmemory[pageToSwap];
    mainmemory[pageToSwap] = pid;
    cout << "Process " << pid << " has been swapped into main memory, replacing process " << processToSwap << endl;
  } else {
    // Find an empty page in main memory
    for (int i = 0; i < mainMemoryCapacity; i++) {
      if (mainmemory[i] == -1) {
        mainmemory[i] = pid;
        cout << "Process " << pid << " has been swapped into main memory" << endl;
        return;
      }
    }
  }
}



int main(int argc, char *argv[]) {
  // argc is the number of arguments, argv is an array of strings
  cout << "****************Welcome to the Memory Management "
          "System****************"
       << endl;
  // M = main memory size in KB
  // V = virtual memory size in KB
  // P = page size in KB
  // infile = input file
  // outfile = output file
  // THESE ARE DEFAULT VALUES
  int M = -1; // Default values
  int V = -1;
  int P = -1;

  cout<<"Default values of M V P respectively"<<M<<" "<<V<<" "<<P<<endl;

  if (argc != 7) {
    std::cerr << "Usage: " << argv[0] << " -M <M> -V <V> -P <P>\n";
    return 1;
  }

  for (int i = 1; i < argc; i += 2) {
    std::string option(argv[i]);
    if (option == "-M") {
      M = std::stoi(argv[i + 1]);
    } else if (option == "-V") {
      V = std::stoi(argv[i + 1]);
    } else if (option == "-P") {
      P = std::stoi(argv[i + 1]);
    } else {
      std::cerr << "Unknown option: " << option << "\n";
      return 1;
    }
  }

  if (M == -1 || V == -1 || P == -1) {
    std::cerr << "Invalid arguments. Usage: " << argv[0]
              << " -M <M> -V <V> -P <P>\n";
    return 1;
  }

  // Now you can use the parsed values
  cout << "M: " << M << "\n";
  cout << "V: " << V << "\n";
  cout << "P: " << P << "\n";
  // cout << "Input file: " << infile << "\n";
  // cout << "Output file: " << outfile << "\n";

  int mainMemoryPages = (M * 1024) / P;
  int virtualMemoryPages = (V * 1024) / P;
  cout << "Number of pages in main memory: " << mainMemoryPages << endl;
  cout << "Number of pages in virtual memory: " << virtualMemoryPages << endl;

  vector<int> mainmemory(mainMemoryPages, -1);
  vector<int> virtualMemory(virtualMemoryPages, -1);
  vector<vector<int>> pageTables;
  for (int i = 0; i < 100; i++) {
    pageTables.push_back(vector<int>(virtualMemoryPages, -1));
  }

  cout << "****************Welcome to the Vedang's terminal****************"
       << endl;
  while (true) {
    cout << "-> ";
    string command;
    cin >> command;
    if (command == "load") {
      getline(cin, command);
      stringstream ss(command);
      string filename;
      while (ss >> filename) {
        load(mainmemory, virtualMemory, P, filename);
      }
    } else if (command == "pte") {
      int pid;
      string filename;
      cin >> pid >> filename;
      pte(mainmemory, pid, filename);
    } else if (command == "exit") {
      break;
    } else if (command == "listpr") {
      listpr(mainmemory, virtualMemory);
    } else if (command == "pteall") {
      string filename;
      cin >> filename;
      pteall(mainmemory, virtualMemory, filename);
    } else if (command == "swapout") {
      int pid;
      cin >> pid;
      swapout(mainmemory, virtualMemory, pid);
    } else if (command == "kill") {
      int pid;
      cin >> pid;
      kill(mainmemory, virtualMemory, pid);
    } else if (command == "printmem") {
      int memloc, length;
      cin >> memloc >> length;
      printMemory(mainmemory, memloc, length);
    }
    else if (command == "run") {
      int pid;
      cin >> pid;
      runexecmd(mainmemory, virtualMemory, pid);
    }
    else if (command == "swapin") {
      int pid;
      cin >> pid;
      executeSwapIn(mainmemory, virtualMemory, pid);
    }

    else {
      cout << "Invalid command" << endl;
    }
  }

  return 0;
}
