using System;
using System.Collections.Generic;

namespace ExampleAIModule
{
	public static class Helper
	{
		public static IEnumerable<TResult> Project<TSource, TResult>(
			this IEnumerable<TSource> source,
			Func<TSource, TSource, TResult> projection)
		{
			using (var iterator = source.GetEnumerator())
			{
				if (!iterator.MoveNext())
				{
					yield break;
				}
				var first = iterator.Current;
				var previous = iterator.Current;
				while (iterator.MoveNext())
				{
					yield return projection(previous, iterator.Current);
					previous = iterator.Current;
				}
				yield return projection(previous, first);
			}
		}
	}
}
