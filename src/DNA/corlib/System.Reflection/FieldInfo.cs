using System.Runtime.CompilerServices;

namespace System.Reflection
{
    public abstract class FieldInfo : MemberInfo
    {
        public override MemberTypes MemberType => MemberTypes.Field;

        public abstract object GetValue(object obj);

        public virtual void SetValue(object obj, object value) {
            throw new NotImplementedException();
        }
    }
}
