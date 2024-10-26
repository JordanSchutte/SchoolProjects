import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Trip } from '../models/trip';
import { TripDataService } from '../services/trip-data.service';
import { AuthenticationService } from '../services/authentication.service';
import { TripCardComponent } from '../trip-card/trip-card.component';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-trip-listing',
  standalone: true,
  imports: [CommonModule, TripCardComponent, RouterLink],
  templateUrl: './trip-listing.component.html',
  styleUrls: ['./trip-listing.component.css']
})
export class TripListingComponent implements OnInit {
  trips: Trip[] = [];
  message: string = '';

  constructor(
    private tripDataService: TripDataService,
    private authService: AuthenticationService
  ) { }

  ngOnInit(): void {
    this.getTrips();
  }

  private getTrips(): void {
    this.tripDataService.getTrips()
      .subscribe(
        (trips: Trip[]) => {
          this.trips = trips;
          this.message = trips.length > 0 ? '' : 'No trips found';
        },
        (error: any) => {
          this.message = 'Error fetching trips';
          console.error(error);
        }
      );
  }

  public isLoggedIn(): boolean {
    return this.authService.isLoggedIn();
  }
}