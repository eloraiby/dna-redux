namespace System.Reflection {
    [Flags]
    public enum BindingFlags {
        Default = 0x0000,
        IgnoreCase = 0x0001,
        DeclaredOnly = 0x0002,
        Instance = 0x0004,
        Static = 0x0008,
        Public = 0x0010,
        NonPublic = 0x0020,
        FlattenHierarchy = 0x0040,
        InvokeMethod = 0x0100,
        CreateInstance = 0x0200,
        GetField = 0x0400,
        SetField = 0x0800,
        GetProperty = 0x1000,
        SetProperty = 0x2000,
        PutDispProperty = 0x4000,
        PutRefDispProperty = 0x8000,
        ExactBinding = 0x010000,
        SuppressChangeType = 0x020000,
        OptionalParamBinding = 0x040000,
        IgnoreReturn = 0x01000000
    }
}
