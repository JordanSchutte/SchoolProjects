import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink, Router } from '@angular/router';
import { Trip } from '../models/trip';
import { AuthenticationService } from '../services/authentication.service';

@Component({
  selector: 'app-trip-card',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './trip-card.component.html',
  styleUrls: ['./trip-card.component.css']
})
export class TripCardComponent {
  @Input() trip!: Trip;

  constructor(
    private authService: AuthenticationService,
    private router: Router
  ) { }

  public isLoggedIn(): boolean {
    return this.authService.isLoggedIn();
  }

  public editTrip(tripCode: string): void {
    this.router.navigate(['edit-trip', tripCode]);
  }
}