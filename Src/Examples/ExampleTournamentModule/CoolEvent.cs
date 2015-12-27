using BroodWar.Api;

namespace ExampleTournamentModule
{
	internal class CoolEvent
	{
		public Position Position { get; set; }
		public Unit Unit { get; set; }
		public int Priority { get; set; }
		public int Timer { get; set; }

		public bool IsNone
		{
			get { return Position == null && Unit == null; }
		}

		public override bool Equals(object obj)
		{
			var other = obj as CoolEvent;
			return Equals(other);
		}

		public static bool operator == (CoolEvent first, CoolEvent second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(first, null) || ReferenceEquals(second, null))
				return false;
			return first.Position == second.Position
				&& first.Unit == second.Unit
				&& first.Priority == second.Priority
				&& first.Timer == second.Timer;
		}

		public static bool operator !=(CoolEvent first, CoolEvent second)
		{
			return !(first == second);
		}

		public bool Equals(CoolEvent other)
		{
			if(ReferenceEquals(null, other))
			{
				return false;
			}
			if(ReferenceEquals(this, other))
			{
				return true;
			}
			return Equals(other.Position, Position) && Equals(other.Unit, Unit) && other.Priority == Priority && other.Timer == Timer;
		}

		public override int GetHashCode()
		{
			unchecked
			{
				int result = (Position != null ? Position.GetHashCode() : 0);
				result = (result * 397) ^ (Unit != null ? Unit.GetHashCode() : 0);
				result = (result * 397) ^ Priority;
				result = (result * 397) ^ Timer;
				return result;
			}
		}
	}
}
