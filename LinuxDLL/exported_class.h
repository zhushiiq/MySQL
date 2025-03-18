#ifndef EXPORTED_CLASS_H
#define EXPORTED_CLASS_H

#ifdef __cplusplus
extern "C" {
#endif

    class __attribute__((visibility("default"))) ExportedClass {
    public:
        ExportedClass();
        ~ExportedClass();
        int add(int a, int b);
    };

#ifdef __cplusplus
}
#endif

#endif // EXPORTED_CLASS_H

