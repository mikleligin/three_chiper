#include <iostream>
using namespace std;

//A = g^a mod p
//B = g^b mod p
//s = B^a mod p
//s = A^b mod p
//g,p-same
int take_key(double g, int p, double a)
{
    
    double x = pow(g, a);
    return int(x) % p;
}
bool are_simple(int number)
{
    if (number < 0 || number==2) return 0;
    for (size_t i = 2; i < number; i++)
    {
        if (number % i == 0) return 0;
    }
    return 1;
}
int dif_hell(int public_mod, int g_key, int secret_a, int secret_b)
{   
    int g = g_key;
    int p = public_mod;
    int a_alice = secret_a;
    int a_bob = secret_b;
    if (are_simple(g) && are_simple(p))
    {
        int A = take_key(g, p, a_alice);
        cout << "Key is a ";
        int B = take_key(g, p, a_bob);
        int result = take_key(B, p, a_alice);
        cout<< "[" <<  result << ",";
        cout << take_key(A, p, a_bob) << "]";
        return result;
    }  
    else
    {
        cout << "The numbers are not a simple";
        return 0;
    }
    
}
int el_first = 0;
int el_second = 0;
int el_secret_x = 0;
int GetRandomNumber(int min, int max)
{
    srand(time(NULL));
    int num = min + rand() % (max - min + 1);
    return num;
}
int el_gamal_encode(int msg, int p_public, int g_public)
{
    el_secret_x = GetRandomNumber(1, p_public - 1);
    int k_secret = GetRandomNumber(1,p_public-1);
    if (el_secret_x >p_public-1 && el_secret_x <1) return 0;
    int y = int(pow(g_public, el_secret_x))%p_public;
    el_first = int(pow(g_public, k_secret))%p_public;
    el_second = int(pow(y, k_secret) * msg) % p_public;
    return 1;
}
int el_gamal_decode(int p)
{
    return fmod(el_second * pow(el_first, p - 1 - el_secret_x), p);
}
int count_to_coprime(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
}
int rsa(int message)
{
    double p = 3;
    double q = 7;
    double n = p * q;
    double count;
    double totient = (p - 1) * (q - 1);
    double e = 2;
    while (e < totient) {
        count = count_to_coprime(e, totient);
        if (count == 1)
            break;
        else
            e++;
    }
    double d;
    double k = 2;
    d = (1 + (k * totient)) / e;
    double msg = message;
    double c = fmod(pow(msg, e), n);
    double m = fmod(pow(c, d), n);

    cout << "Msg = " << msg;
    cout << "\n" << '\t'<<"Decode msg = " << m<<"\n\n";

    return 0;
    
}
int main()
{
    //************************
    printf("\033[97m\033[45m");
    cout << "Diffie-Hellman"<<endl;
    printf("\033[39m\033[49m");
    cout << '\t';
    dif_hell(11,7,3,6);//9
    cout << '\n';
    //************************
    printf("\033[97m\033[46m");
    cout<<"el_gamal"<<endl;
    el_gamal_encode(5,11,2);
    printf("\033[39m\033[49m");
    cout << '\t';
    cout << "Msg is " << 5<<endl;
    cout <<"\tDecode msg is " << el_gamal_decode(11) << endl;
    
    //************************
    printf("\033[97m\033[101m");
    cout << "RSA" << endl;
    printf("\033[39m\033[49m");
    cout << '\t';
    rsa(12);

}