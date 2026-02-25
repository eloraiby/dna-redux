namespace System.Reflection {
    public abstract class PropertyInfo : MemberInfo {

#pragma warning disable 0649
        private readonly Type _propertyType;
#pragma warning restore 0649

        public override MemberTypes MemberType => MemberTypes.Property;

        public Type PropertyType => _propertyType;

        public MethodInfo GetGetMethod() {
            return _ownerType.GetMethod("get_" + Name);
        }

        public MethodInfo GetGetMethod(bool nonPublic) {
            return GetGetMethod();
        }

        public MethodInfo GetSetMethod() {
            return _ownerType.GetMethod("set_" + Name);
        }

        public MethodInfo GetSetMethod(bool nonPublic) {
            return GetSetMethod();
        }

        public MethodInfo GetMethod => GetGetMethod();
        public MethodInfo SetMethod => GetSetMethod();

        public virtual object GetValue(object obj, object[] index) {
            object ret = null;

            MethodInfo method = GetGetMethod ();
            if (method == null)
                throw new ArgumentException ("Get Method not found for '" + Name + "'");

            if (index == null || index.Length == 0) {
                ret = method.Invoke (obj, null);
            } else {
                ret = method.Invoke (obj, index);
            }

            return ret;
        }

        public virtual object GetValue(object obj, BindingFlags invokeAttr, Binder binder, object[] index, System.Globalization.CultureInfo culture) {
            return GetValue(obj, index);
        }

        public virtual void SetValue (object obj, object value, object[] index) {
            MethodInfo method = GetSetMethod ();
            if (method == null)
                throw new ArgumentException ("Set Method not found for '" + Name + "'");
            
            object [] parms;
            if (index == null || index.Length == 0) {
                parms = new object [] { value };
            } else {
                int ilen = index.Length;
                parms = new object [ilen + 1];
                index.CopyTo (parms, 0);
                parms [ilen] = value;
            }

            method.Invoke (obj, parms);
        }

        public virtual void SetValue(object obj, object value, BindingFlags invokeAttr, Binder binder, object[] index, System.Globalization.CultureInfo culture) {
            SetValue(obj, value, index);
        }
    }
}
