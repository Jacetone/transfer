ls
mkdir temp
cd temp
ls
git clone const unsigned int num_cpus = std::thread::hardware_concurrency(); // The total number of CPUs on the system. Will be 24 for OpenHPC. 
std::vector<std::thread> threads; 
for (int i = 0; i < num_threads; ++i)
{     std::thread temp(func, args...); //Or pthread
    threads.push_back(std::move(temp));
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET( (i % num_cpus ), &cpuset);
     int rc = pthread_setaffinity_np(threads[i].native_handle(),
                                                      sizeof(cpu_set_t), &cpuset);
    if (rc != 0){
       std::cerr << "Error setting affinity" << '\n';
    }
git clone const unsigned int num_cpus = std::thread::hardware_concurrency(); // The total number of CPUs on the system. Will be 24 for OpenHPC. 
std::vector<std::thread> threads; 

for (int i = 0; i < num_threads; ++i)
{
    std::thread temp(func, args...); //Or pthread
    threads.push_back(std::move(temp));

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET( (i % num_cpus ), &cpuset);

     int rc = pthread_setaffinity_np(threads[i].native_handle(),
                                                      sizeof(cpu_set_t), &cpuset);
    if (rc != 0){
       std::cerr << "Error setting affinity" << '\n';
    }




sl
ls
ls ..
ls
git clone https://github.com/bu-cs547-2020-1s/assignment-1-ctrembl1
ls
git clone https://github.com/bu-cs547-2020-1s/assignment-1-ctremblay04
ls
cd assignment-1-ctremblay04/
ls
module load gnu9
module load gnu8
module load conda
pip install --user pandas
ls
cp tester.py ~
ls
cd
lks
ls
make
python tester.py 
pip install --user pandas
pip install plotly
pip install --user plotly
python tester.py 
ls
vim tester.py 
ls
scp *.html zachf@149.125.32.32
scp *.html zachf@149.125.32.32:
scp *.html zachf@149.125.32.32:~
python tester.py 
ls
rm -rf temp
ls
make clean
make
ls
make clean
ls
vim tester.py 
