#include <typeinfo>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

//Note, this function is not optimized and is for illustration purposes
//  see void multiply_any(int digits, LowType *a, LowType *b, LowType *c) which handles zeros more like multiplication in actual practice
void multiply_uint32_t(int digits, uint32_t *a, uint32_t *b, uint32_t *c)
{
    uint32_t carry;

    for (int place_c=0; place_c < digits*2; place_c++) c[place_c] = 0;

    //for each digit in a
    for (int place_a=0; place_a<digits; place_a++) {
        int place_b;

        carry = 0;

        //multiply with the digits in b
        for (place_b = 0; place_b < digits; place_b++) {
            uint64_t v = carry + a[place_a] * (uint64_t) b[place_b] + c[place_a + place_b];

            uint32_t low = (uint32_t) v; //store the low half
            uint32_t high = (uint32_t) v>>32; //store the high half;

            c[place_a + place_b] = low;
            carry = high;
        }

        //process the carry
        for (; carry != 0 && place_b < digits * 2; place_b++)
        {
            uint64_t v = carry + c[place_a + place_b];

            uint32_t low = (uint32_t) v; //store the low half
            uint32_t high = (uint32_t) v>>32; //store the high half;

            c[place_a + place_b] = low;
            carry = high;
        }
    }
}


template<typename LowType, typename HighType>
void multiply_any(int digits, LowType *a, LowType *b, LowType *c)
{
    LowType carry;

    for (int place_c=0; place_c < digits*2; place_c++) c[place_c] = 0;

    //for each digit in a
    for (int place_a=0; place_a<digits; place_a++) {
        int place_b;

        carry = 0;

        if (a[place_a] ==0) continue;

        //multiply with the digits in b
        for (place_b = 0; place_b < digits; place_b++) {
            HighType v;

            if (b[place_b] != 0) {
                v = carry + a[place_a] * (HighType) b[place_b] + c[place_a + place_b];;
            } else {
                v = carry + c[place_a + place_b];
            }
            carry = (LowType) (v >> (sizeof(LowType)*8));
            c[place_a + place_b] = (LowType) v;

        }

        //process the carry
        for (; carry != 0 && place_b < digits * 2; place_b++)
        {
            HighType v = carry + c[place_a + place_b];

            c[place_a + place_b] = (LowType) v;
            carry = (LowType) (v >> (sizeof(LowType)*8));

        }
    }
}

class Node
{
public:
    const std::type_info *ti;
    char name[1024];

    Node *Next = nullptr;

    Node(const std::type_info *ti, const char *name)
    {
        this->ti = ti;

        int i;
        for (i=0; i<1023; i++)
        {
            if (name[i] == 0) break;
            this->name[i] = name[i];
        }

        this->name[i] = 0;
    }

    const char *GetName(const std::type_info *t)
    {
        for (Node *N = this; N != nullptr; N = N->Next)
            if (N->ti == t) return N->name;
        return nullptr;
    }
};

Node Head(NULL, "");

template<typename LowType, typename HighType>
void multiply_uint64_t(uint64_t a, uint64_t b)
{
    const int digits = sizeof(uint64_t) / sizeof(LowType);
    LowType _a[digits];
    LowType _b[digits];
    LowType _c[digits*2];

    uint64_t a_q = a;
    uint64_t b_q = b;

    const int shift = sizeof(LowType)<<3;

    for (int digit=0; digit < digits; digit++)
    {
        _a[digit] = (LowType) a_q;
        _b[digit] = (LowType) b_q;

        a_q >>= shift;
        b_q >>= shift;
    }

    multiply_any<LowType,HighType>(digits, _a, _b, _c);

    char FormatString[1024];

    sprintf(FormatString, "%s%ldX", "%0", sizeof(LowType)*2);

    printf("%s: ", Head.GetName(&typeid(LowType)));
    fflush(stdout);

    for (int i=digits-1; i>=0; i--)
    {
        printf(FormatString, (int) _a[i]);
        fflush(stdout);
    }

    printf(" * ");
    fflush(stdout);

    for (int i=digits-1; i>=0; i--)
    {
        printf(FormatString, (int) _b[i]);
        fflush(stdout);
    }

    printf(" = ");
    fflush(stdout);

    for (int i=(digits<<1)-1; i>=0; i--)
    {
        printf(FormatString, (int) _c[i]);
        fflush(stdout);
    }

    printf("\n");
    fflush(stdout);

}

void test(uint64_t a, uint64_t b)
{
    multiply_uint64_t<uint8_t, uint16_t>(a, b);
    multiply_uint64_t<uint16_t, uint32_t>(a, b);
    multiply_uint64_t<uint32_t, uint64_t>(a, b);

}

uint64_t Getuint64_t()
{
    uint64_t R = 0;
    for (int i=0; i < 8; i++)
    {
        ((unsigned char *)&R)[i] = rand() % 0xFF;
    }

    return R;
}

int main(int argc, char **argv) {
    printf("%X\n", 0xFF * 0xFF);

    uint64_t a = 0x1000000010000001ul;
    uint64_t b = 0x2000000000000002ul;

    Node *Cur = &Head;

    Node *q;

    q = new Node(&typeid(uint8_t), "uint8_t");
    Cur = Cur->Next = q;
    q = new Node(&typeid(uint16_t), "uint16_t");
    Cur = Cur->Next = q;
    q = new Node(&typeid(uint32_t), "uint32_t");
    Cur = Cur->Next = q;
    q = new Node(&typeid(uint64_t), "uint64_t");
    Cur = Cur->Next = q;


    test(a,b);

    srand(0);

    printf("run carry\n");
    test(0xFFFFFFFFFFFFFFFFul, 0xFFFFFFFFFFFFFFFFul);

    for (int i=0; i<4; i++) {
        printf("run %d\n", i);
        a = Getuint64_t();
        b = Getuint64_t();

        test(a, b);
    }

    return 0;
}