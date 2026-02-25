using System.Runtime.CompilerServices;

namespace System.Reflection
{
    public abstract class ConstructorInfo : MethodBase
    {
        public override MemberTypes MemberType => MemberTypes.Constructor;

        public object Invoke(object[] parameters) {
            return Invoke(null, parameters);
        }

        public object Invoke(BindingFlags invokeAttr, Binder binder, object[] parameters, System.Globalization.CultureInfo culture) {
            return Invoke(null, parameters);
        }
    }
}
